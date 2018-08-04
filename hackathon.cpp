/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */
#include "hackathon.hpp"
#include <boost/algorithm/string.hpp>

using namespace eosio;
using namespace std;

namespace hackthon {
    biocoin::biocoin(account_name self) : contract(self), _requests(self, self) {

    }

    void
    biocoin::submit(account_name user_id, vector<string> images, double longitude, double latitude, string sample_name,
                    string sample_category) {
        _requests.emplace(_self, [&](auto &r) {
            r.id = _requests.available_primary_key();
            r.user_id = user_id;
            r.images = images;
            r.longitude = longitude;
            r.latitude = latitude;
            r.sample_name = sample_name;
            r.sample_category = sample_category;
            r.weight = 0;
            r.target_weight = 3;
            r.assigned_expert_num = 3;
            r.processed_expert_num = 0;
            r.assigned_experts = {N(expert111111), N(expert222222), N(expert333333), N(expert444444), N(expert555555)};
            r.processed_experts = {};
            r.status = 1;
        });
    }

    void biocoin::check(account_name client, uint64_t id) {
        require_auth(client);
        auto req_itr = _requests.find(id);
        eosio_assert(req_itr != _requests.end(), "can not find request");
        eosio_assert(req_itr->status != 1, "request has not been finished processing.");
        eosio_assert(req_itr->status != 2, "request was rejected");
        eosio_assert(req_itr->status != 4, "rewards have been claimed");
        eosio_assert(req_itr->status == 3, "rewards can not be claimed");

        _requests.modify(req_itr, _self, [&](auto &r) {
            auto en = req_itr->expert_notes;
            map<string, int> counter_sample_name;
            map<string, int> counter_category_name;
            for (auto const &expert_note : en) {
                if(expert_note.result > 0){
                    counter_sample_name[expert_note.sample_name] += 1;
                    counter_category_name[expert_note.sample_category] += 1;
                }
            }
            int currentMax = 0;
            string final_name = req_itr->sample_name;
            for (auto it = counter_sample_name.cbegin(); it != counter_sample_name.cend(); ++it) {
                if (it->second >= currentMax) {
                    final_name = it->first;
                    currentMax = it->second;
                }
            }

            currentMax = 0;
            string final_category = req_itr->sample_category;
            for (auto it = counter_category_name.cbegin(); it != counter_category_name.cend(); ++it) {
                if (it->second >= currentMax) {
                    final_category = it->first;
                    currentMax = it->second;
                }
            }

            r.final_name = final_name;
            r.final_category = final_category;

        });


        INLINE_ACTION_SENDER(eosio::token, transfer)(N(eosio.token), {_self, N(active)},
                                                     {_self, client, asset(100000), "rewards for client"});
        auto pe = req_itr->processed_experts;
        for (auto const &expert: pe) {
            INLINE_ACTION_SENDER(eosio::token, transfer)(N(eosio.token), {_self, N(active)},
                                                         {_self, expert, asset(10000), "rewards for expert"});
        }
    }

    void biocoin::verify(account_name expert, uint64_t id, uint32_t result, string sample_name, string sample_category,
                         string remark) {
        require_auth(expert);
        auto req_itr = _requests.find(id);
        eosio_assert(req_itr != _requests.end(), "can not find request");
        eosio_assert(req_itr->status == 1, "request has finished processing");

        note note = {expert, result, sample_name, sample_category, remark};

        _requests.modify(req_itr, _self, [&](auto &r) {
            auto ae = r.assigned_experts;
            auto assign_expert_itr = find(ae.begin(), ae.end(), expert);
            eosio_assert(assign_expert_itr != ae.end(), "not an assigned expert");
            ae.erase(assign_expert_itr);
            r.assigned_experts = ae;

            auto pe = r.processed_experts;
            auto processed_expert_itr = find(pe.begin(), pe.end(), expert);
            eosio_assert(processed_expert_itr == pe.end(), "you have processed the request");

            r.weight += result;
            r.processed_expert_num++;
            r.processed_experts.emplace_back(expert);

            r.expert_notes.emplace_back(note);

            if (r.weight >= r.target_weight) {
                r.status = 3;
            } else if (r.processed_expert_num == r.assigned_expert_num && r.weight < r.target_weight) {
                r.status = 2;
            }
        });
    }

}
