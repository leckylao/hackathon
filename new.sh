#!/usr/bin/env bash

#Private key: 5KXpr9VFSgKp3mpijXi5XFC6PMeGeTZJBKBemg1Mv7pFuhv1oSt
#Public key: EOS66BM6ghtyojnfmZKgGX9kADxVsbpPii65jCqaCPfD2cWYvvioS

set -e
set -x
contract=hackathon114
remote=""

cleos system newaccount eosio ${contract} EOS66BM6ghtyojnfmZKgGX9kADxVsbpPii65jCqaCPfD2cWYvvioS EOS66BM6ghtyojnfmZKgGX9kADxVsbpPii65jCqaCPfD2cWYvvioS --stake-net "100 EOS" --stake-cpu "100 EOS" --buy-ram-kbytes 1000 -p eosio