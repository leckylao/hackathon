#!/usr/bin/env bash

contract=hackathon114


cleos push action ${contract}  verify '{"expert":"expert111111","id":0,"result":1}' -p expert111111