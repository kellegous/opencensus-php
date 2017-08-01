# OpenCensus - A stats collection and distributed tracing framework

This is the open-source release of Census for Python. Census provides a
framework to measure a server's resource usage and collect performance stats.
This repository contains PHP related utilities and supporting software needed by
Census.

## Installation

1. Install with `composer` or add to your `composer.json`.

```
$ composer require opencensus/opencensus
```

2. Include and start the library as the first action in your application:

```php
use OpenCensus\Trace\RequestTracer;
use OpenCensus\Trace\Reporter\EchoReporter;

RequestTracer::start(new EchoReporter());
```

## Customizing

### Reporting Traces

The above sample uses the `EchoReporter` to report dump trace results to the
bottom of the webpage.

If you would like to provide your own reporter, create a class that implements `ReporterInterface`.

### Sampling Rate

By default we attempt to trace all requests. This is not ideal as a little bit of
latency and require more memory for requests that are traced. To trace a sampling
of requests, configure a sampler.

The preferred sampler is the `QpsSampler` (Queries Per Second). This sampler implementation
requires a PSR-6 cache implementation to function.

```php
use OpenCensus\Trace\Reporter\EchoReporter;
use OpenCensus\Trace\Sampler\QpsSampler;

$cache = new SomeCacheImplementation();
$sampler = new QpsSampler($cache, ['rate' => 0.1]); // sample 0.1 requests per second
RequestTracer::start(new EchoReporter(), ['sampler' => $sampler]);
```

Please note: While required for the `QpsSampler`, a PSR-6 implementation is
not included in this library. It will be necessary to include a separate
dependency to fulfill this requirement. For PSR-6 implementations, please see the
[Packagist PHP Package Repository](https://packagist.org/providers/psr/cache-implementation).
If the APCu extension is available (available on Google AppEngine Flexible Environment)
and you include the cache/apcu-adapter composer package, we will set up the cache for you.

You can also choose to use the `RandomSampler` which simply samples a flat
percentage of requests.

```php
use OpenCensus\Trace\Reporter\EchoReporter;
use OpenCensus\Trace\Sampler\RandomSampler;

$sampler = new RandomSampler(0.1); // sample 10% of requests
RequestTracer::start(new EchoReporter(), ['sampler' => $sampler]);
```

If you would like to provide your own sampler, create a class that implements `SamplerInterface`.

## Tracing Code Blocks

To add tracing to a block of code, you can use the closure/callable form or explicitly open
and close spans yourself.

### Closure/Callable (preferred)

```php
$pi = RequestTracer::inSpan(['name' => 'expensive-operation'], function() {
    // some expensive operation
    return calculatePi(1000);
});

$pi = RequestTracer::inSpan(['name' => 'expensive-operation'], 'calculatePi', [1000]);
```

### Explicit Span Management

```php
RequestTracer::startSpan(['name' => 'expensive-operation']);
try {
    $pi = calculatePi(1000);
} finally {
    // Make sure we close the span to avoid mismatched span boundaries
    RequestTracer::endSpan();
}
```

### OpenCensus extension
