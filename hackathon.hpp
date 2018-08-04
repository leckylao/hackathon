#include <eosiolib/eosio.hpp>
#include <eosiolib/singleton.hpp>
#include <eosio.token/eosio.token.hpp>
#include <eosiolib/time.hpp>

namespace hackthon {
    using namespace eosio;
    using namespace std;
    using eosio::indexed_by;
    using eosio::const_mem_fun;
    using eosio::block_timestamp;


    class biocoin : public contract {
    private:
        //@abi table
        struct request {
            uint64_t  id;
            account_name user_id;
            vector<string> images;
            string longitude;
            string latitude;
            string sample_name;
            string sample_category;

            uint32_t weight;
            uint32_t target_weight;
            uint32_t assigned_expert_num;
            uint32_t processed_expert_num;
            vector<account_name> assigned_experts;
            vector<account_name> processed_experts;


            uint32_t status; //1 processing  , 2 rejected , 3 approved

            uint64_t primary_key() const { return id; }

            EOSLIB_SERIALIZE(request, (id)(user_id)(images)(longitude)(latitude)(sample_name)(sample_category)
                    (weight)(target_weight)(assigned_expert_num)(processed_expert_num)(assigned_experts)(processed_experts)(status)
            )
        };
        typedef multi_index<N(request), request> request_table;
        request_table _requests;


    public:
        explicit biocoin(account_name self);

        //@abi action
        void submit(account_name user_id, vector<string> images, double longitude, double latitude,string sample_name,string sample_category );

        //@abi action
        void check(account_name client, uint64_t id);

        //@abi action
        void verify(account_name expert, uint64_t id, uint32_t result);
    };

}


EOSIO_ABI(hackthon::biocoin, (submit)(check)(verify))
