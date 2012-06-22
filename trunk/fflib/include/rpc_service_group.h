//! rpc 服务组
#ifndef _RPC_SERVICE_GROUP_H_
#define _RPC_SERVICE_GROUP_H_

#include <stdint.h>
#include <map>
using namespace std;

#include "rpc_service.h"

class rpc_service_group_t
{
    typedef map<uint16_t, rpc_service_t*>   rpc_service_map_t;
public:
    rpc_service_group_t(const string& name_, uint16_t id_);
    ~rpc_service_group_t();

    uint16_t get_id() const;
    const string& get_name() const;

    rpc_service_t* get_service(uint16_t id_);

    int add_service(uint16_t id_, rpc_service_t* service_);
    rpc_service_t& create_service(uint16_t id_);

private:
    uint16_t            m_id;
    string              m_name;
    rpc_service_map_t   m_all_rpc_service;
};

rpc_service_group_t::rpc_service_group_t(const string& name_, uint16_t id_):
    m_id(id_),
    m_name(name_)
{}

rpc_service_group_t::~rpc_service_group_t()
{
    rpc_service_map_t::iterator it = m_all_rpc_service.begin();
    for (; it != m_all_rpc_service.end(); ++it)
    {
        delete it->second;
    }
    m_all_rpc_service.clear();
}

uint16_t rpc_service_group_t::get_id() const
{
    return m_id;
}

const string& rpc_service_group_t::get_name() const
{
    return m_name;
}

rpc_service_t* rpc_service_group_t::get_service(uint16_t id_)
{
    rpc_service_map_t::iterator it = m_all_rpc_service.find(id_);
    if (it != m_all_rpc_service.end())
    {
        return it->second;
    }
    return NULL;
}

int rpc_service_group_t::add_service(uint16_t id_, rpc_service_t* service_)
{
    return m_all_rpc_service.insert(make_pair(id_, service_)).second == true? 0: -1;
}

rpc_service_t& rpc_service_group_t::create_service(uint16_t id_)
{
    for (rpc_service_map_t::iterator it = m_all_rpc_service.begin(); it != m_all_rpc_service.end(); ++it)
    {
        if (id_ == it->second->get_id())
        {
            return *(it->second);
        }
    }

    rpc_service_t* rs = new rpc_service_t(m_id, id_);
    this->add_service(id_, rs);
    return *rs;
}
#endif