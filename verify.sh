#!/usr/bin/env bash

contract=hackathon222


cleos push action ${contract}  verify '
{
"expert":"expert444444","id":0,"result":5,
"sample_name":"ff",
"sample_category":"ff",
"remark":"fdsf"
}' -p expert444444