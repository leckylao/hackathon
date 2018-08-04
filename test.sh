#!/usr/bin/env bash

#cleos -u http://192.168.50.118:8888 set contract localtest111 . fomo.wast fomo.abi -p localtest111
set -e
set -x
#contract=testnethhhhh
#remote="-u http://47.75.115.225:8888"

contract=hackathon223
remote=""

eosiocpp -g hackathon.abi hackathon.hpp
eosiocpp -o hackathon.wast hackathon.cpp

#cleos push action ${contract} dropdb '' -p ${contract}

cd ../../build/contracts/hello
cleos ${remote} set contract ${contract} . hello.wast hello.abi -p ${contract}
cd -

cleos ${remote} set contract ${contract} . hackathon.wast hackathon.abi -p ${contract}

#cleos ${remote} transfer alice1111111 ${contract} "1 EOS" "" -p alice1111111
#cleos ${remote} transfer alice1111111 ${contract} "2 EOS" "" -p alice1111111
#cleos ${remote} transfer bob111111111 ${contract} "1 EOS" "" -p bob111111111
#cleos ${remote} transfer bob111111111 ${contract} "3 EOS" "" -p bob111111111



#cleos system newaccount eosio dev111111111 EOS4v9UCqsPxKkfm267Q1xJbuE6KRbrXLamGQpo45ZS5xfJqMkaDP EOS4v9UCqsPxKkfm267Q1xJbuE6KRbrXLamGQpo45ZS5xfJqMkaDP --stake-cpu "1000 EOS" --stake-net "1000 EOS" --buy-ram "1000 EOS" -p eosio
#cleos transfer eosio dev111111111 "1000 EOS" "red packet" -p eosio

#cleos system newaccount eosio system111111 EOS4v9UCqsPxKkfm267Q1xJbuE6KRbrXLamGQpo45ZS5xfJqMkaDP EOS4v9UCqsPxKkfm267Q1xJbuE6KRbrXLamGQpo45ZS5xfJqMkaDP --stake-cpu "1000 EOS" --stake-net "1000 EOS" --buy-ram "1000 EOS" -p eosio
#cleos transfer eosio system111111 "1000 EOS" "red packet" -p eosio


#cleos -u http://47.75.115.225:8888 system newaccount eosio testnetbbbbb EOS4v9UCqsPxKkfm267Q1xJbuE6KRbrXLamGQpo45ZS5xfJqMkaDP EOS4v9UCqsPxKkfm267Q1xJbuE6KRbrXLamGQpo45ZS5xfJqMkaDP --stake-cpu "1000 EOS" --stake-net "1000 EOS" --buy-ram "1000 EOS" -p eosio
#cleos -u http://47.75.115.225:8888 transfer eosio testnetbbbbb "100 EOS" "red packet" -p eosio

#cleos push action eosio updateauth '["localtest444","active","owner",{"threshold":1,"keys":[{"key":"EOS4v9UCqsPxKkfm267Q1xJbuE6KRbrXLamGQpo45ZS5xfJqMkaDP","weight":1}],"waits":[],"accounts":[{"weight":1,"permission":{"actor":"localtest444","permission":"eosio.code"}}]}]' -p localtest444
#cleos -u http://47.75.115.225:8888 push action eosio updateauth '["testnetggggg","active","owner",{"threshold":1,"keys":[{"key":"EOS4v9UCqsPxKkfm267Q1xJbuE6KRbrXLamGQpo45ZS5xfJqMkaDP","weight":1}],"waits":[],"accounts":[{"weight":1,"permission":{"actor":"testnetggggg","permission":"eosio.code"}}]}]' -p testnetggggg

#while true; do cleos -u http://47.75.115.225:8888 push action testnetggggg dividepool '{"round_id":8}' -p alice1111111; sleep 1; done


cleos push action eosio updateauth '["hackathon223","active","owner",{"threshold":1,"keys":[{"key":"EOS66BM6ghtyojnfmZKgGX9kADxVsbpPii65jCqaCPfD2cWYvvioS","weight":1}],"waits":[],"accounts":[{"weight":1,"permission":{"actor":"hackathon223","permission":"eosio.code"}}]}]' -p hackathon223
