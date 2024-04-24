
<!-- README.md is generated from README.Rmd. Please edit that file -->

# secretbase

<!-- badges: start -->

[![CRAN
status](https://www.r-pkg.org/badges/version/secretbase?color=42147b)](https://CRAN.R-project.org/package=secretbase)
[![secretbase status
badge](https://shikokuchuo.r-universe.dev/badges/secretbase?color=e4723a)](https://shikokuchuo.r-universe.dev/secretbase)
[![R-CMD-check](https://github.com/shikokuchuo/secretbase/workflows/R-CMD-check/badge.svg)](https://github.com/shikokuchuo/secretbase/actions)
[![codecov](https://codecov.io/gh/shikokuchuo/secretbase/graph/badge.svg)](https://app.codecov.io/gh/shikokuchuo/secretbase)
[![DOI](https://zenodo.org/badge/745691432.svg)](https://zenodo.org/doi/10.5281/zenodo.10553139)
<!-- badges: end -->

Fast and memory-efficient streaming hash functions. Performs direct
hashing of strings, raw bytes, and files potentially larger than memory,
as well as hashing in-memory objects through R’s serialization
mechanism, without requiring allocation of the serialized object.

Implementations include the SHA-256, SHA-3 and Keccak cryptographic hash
functions, SHAKE256 extendable-output function (XOF), and ‘SipHash’
pseudo-random function.

The SHA-3 Secure Hash Standard was published by the National Institute
of Standards and Technology (NIST) in 2015 at
[doi:10.6028/NIST.FIPS.202](https://dx.doi.org/10.6028/NIST.FIPS.202).
The SHA-256 Secure Hash Standard was published by NIST in 2002 at
<https://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf>. The
SipHash family of pseudo-random functions by Jean-Philippe Aumasson and
Daniel J. Bernstein was published in 2012 at
<https://ia.cr/2012/351>.<sup>\[1\]</sup>

The SHA-256 and SHA-3 implementations are based on those by the ‘Mbed
TLS’ Trusted Firmware Project at
<https://www.trustedfirmware.org/projects/mbed-tls>. The SipHash
implementation is based on that of Daniele Nicolodi, David Rheinsberg
and Tom Gundersen at <https://github.com/c-util/c-siphash>, which is in
turn based on the reference implementation by Jean-Philippe Aumasson and
Daniel J. Bernstein released to the public domain at
<https://github.com/veorq/SipHash>.

### Installation

Install the latest version from CRAN:

``` r
install.packages("secretbase")
```

Or the development version from R-universe:

``` r
install.packages("secretbase", repos = "https://shikokuchuo.r-universe.dev")
```

### Quick Start

``` r
library(secretbase)
```

#### SHA-3

- For the SHA-3 cryptographic hash algorithm, specify ‘bits’ as `224`,
  `256`, `384` or `512`

``` r
sha3("secret base")
#> [1] "a721d57570e7ce366adee2fccbe9770723c6e3622549c31c7cab9dbb4a795520"

sha3("secret base", convert = FALSE)
#>  [1] a7 21 d5 75 70 e7 ce 36 6a de e2 fc cb e9 77 07 23 c6 e3 62 25 49 c3 1c 7c
#> [26] ab 9d bb 4a 79 55 20

sha3("秘密の基地の中", bits = 512)
#> [1] "e30cdc73f6575c40d55b5edc8eb4f97940f5ca491640b41612e02a05f3e59dd9c6c33f601d8d7a8e2ca0504b8c22f7bc69fa8f10d7c01aab392781ff4ae1e610"
```

#### Hash arbitrary R objects

- Character strings and raw vectors (without attributes) are hashed ‘as
  is’
- Other objects are hashed using memory-efficient ‘streaming’
  serialization, without allocation of the serialized object
- Portable as always uses R serialization version 3 big-endian
  representation, skipping headers (which contain R version and native
  encoding information)

``` r
sha3(data.frame(a = 1, b = 2), bits = 224)
#> [1] "03778aad53bff7dd68caab94374bba6f07cea235fb97b3c52cf612e9"

sha3(NULL)
#> [1] "b3e37e4c5def1bfb2841b79ef8503b83d1fed46836b5b913d7c16de92966dcee"
```

#### Hash files

- Performed in a streaming fashion, accepting files larger than memory

``` r
file <- tempfile(); cat("secret base", file = file)
sha3(file = file)
#> [1] "a721d57570e7ce366adee2fccbe9770723c6e3622549c31c7cab9dbb4a795520"
```

#### Hash to integer / SHAKE256 XOF

- Specify ‘convert’ as `NA` (and ‘bits’ as `32` for a single integer
  value)
- May be supplied as deterministic random seeds for R’s pseudo random
  number generators (RNGs)

``` r
shake256("秘密の基地の中", bits = 32, convert = NA)
#> [1] 2000208511
```

For use in parallel computing, this is a valid method for reducing to a
negligible probability that RNGs in each process may overlap. This may
be especially suitable when first-best alternatives such as using
recursive streams are too expensive or unable to preserve
reproducibility. <sup>\[2\]</sup>

#### Keccak

``` r
keccak("secret base", bits = 384)
#> [1] "c82bae24175676028e44aa08b9e2424311847adb0b071c68c7ea47edf049b0e935ddd2fc7c499333bccc08c7eb7b1203"
```

#### SHA-256

``` r
sha256("secret base")
#> [1] "1951c1ca3d50e95e6ede2b1c26fefd0f0e8eba1e51a837f8ccefb583a2b686fe"
```

- For a SHA-256 HMAC, pass a character string or raw vector to ‘key’

``` r
sha256("secret base", key = "秘密の基地の中")
#> [1] "ec58099ab21325e792bef8f1aafc0a70e1a7227463cfc410931112705d753392"
```

#### SipHash

- SipHash-1-3 is optimized for performance
- Pass a character string or raw vector to ‘key’ - up to 16 bytes (128
  bits) of the key data is used

``` r
siphash13("secret base", key = charToRaw("秘密の基地の中"))
#> [1] "a1f0a751892cc7dd"
```

### References

\[1\] Jean-Philippe Aumasson and Daniel J. Bernstein (2012), *“SipHash:
a fast short-input PRF”*, Paper 2012/351, Cryptology ePrint Archive,
<https://ia.cr/2012/351>.

\[2\] Pierre L’Ecuyer, David Munger, Boris Oreshkin and Richard Simard
(2017), *“Random numbers for parallel computers: Requirements and
methods, with emphasis on GPUs”*, Mathematics and Computers in
Simulation, Vol. 135, May 2017, pp. 3-17
[doi:10.1016/j.matcom.2016.05.00](https://doi.org/10.1016/j.matcom.2016.05.005).

### Links

Links:

◈ secretbase R package: <https://shikokuchuo.net/secretbase/>

Mbed TLS website:
<https://www.trustedfirmware.org/projects/mbed-tls><br /> SipHash
streaming implementation: <https://github.com/c-util/c-siphash><br />
SipHash reference implementation: <https://github.com/veorq/SipHash>

–

Please note that this project is released with a [Contributor Code of
Conduct](https://shikokuchuo.net/secretbase/CODE_OF_CONDUCT.html). By
participating in this project you agree to abide by its terms.
