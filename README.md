# Optimized SMAUG-T on 16-bit MSP430

This repository provides an optimized implementation of [SMAUG-T](https://kpqc.cryptolab.co.kr/smaug-t), a lattice-based key encapsulation mechanism (KEM) proposed in the [Korean Post-Quantum Cryptography (KPQC) Competition](https://kpqc.or.kr/competition_02.html).   While the original implementation uses Toom–Cook and Karatsuba multiplication, this work replaces the polynomial multiplication routines with a fully optimized NTT-based implementation for the 16-bit MSP430 microcontroller.

This repository serves as the artifact accompanying our paper: \
**“Optimized implementation of SMAUG-T on resource-constrained 16-bit MSP430 MCU”** \
*MinGi Kim, DongHyun Shin, WooHyung Ko, YoungBeom Kim, Seog Chung Seo*\
Published in *ICT Express*, 2025. [DOI: 10.1016/j.icte.2025.07.007](https://doi.org/10.1016/j.icte.2025.07.007)

## Benchmark Setup

We measured performance using the **clock cycle register provided by IAR Embedded Workbench (EW)** for MSP430. All code was tested with the **high(speed)** compiler optimization option on the **MSP430F6779** platform.

## Reference Implementation

This work builds upon the timing-secure reference implementation of SMAUG-T provided by the authors in  
["SMAUG (-T), Revisited: Timing-Secure, More Compact, Less Failure"](http://ieeexplore.ieee.org/document/10776768).  
- All other cryptographic operations remain unchanged.  
- The reference implementation is available at: [https://kpqc.cryptolab.co.kr/smaug-t](https://kpqc.cryptolab.co.kr/smaug-t)
