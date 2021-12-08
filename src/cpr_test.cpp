/**
 * @file cpr_test.cpp
 * @brief  testing CPR to download data from SVO
 * @version 0.1
 *
 */
#include <iostream>
#include <cpr/cpr.h>
#include "cphot/filter.hpp"
#include "cphot/io.hpp"
#include "cphot/votable.hpp"

/**
 * @brief main interface to SVO data requests
 *
 * @param id              passband id
 * @return std::string    data content
 */
std::string download_svo_filter(std::string id){
    cpr::Response r = cpr::Get(cpr::Url{"http://svo2.cab.inta-csic.es/theory/fps/fps.php"},
                               cpr::Parameters{{"ID", id}});

    std::cout << "\n URL: " << r.url << std::endl;
    std::cout << "\n Content: \n" << r.text << std::endl;
    return r.text;
}


int main(){
    const auto xml = download_svo_filter("GAIA/GAIA3.G");
    std::cout << xml << "\n";

    votable::VOTable vot;
    vot.from_content(xml);
    std::cout << vot << "\n";
    auto filt = cphot::get_filter(vot);
    filt.info();
}