#!/usr/bin/env bash

contract=hackathon223


cleos push action ${contract} submit '
{
"user_id":"alice1111111",
"images":["aa"],
"longitude":1.1,
"latitude":1.2,
"sample_name":"test_name",
"sample_category":"test_category",

}' -p alice1111111