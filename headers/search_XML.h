#ifndef search_XML_h
#define search_XML_hclTabCtrl
#include "process.h"

std::string search_query(graph xml_data,std::string request){
    std::string current_serve;
    int count=0;
    int start=0;
    graph new_xml_data;
    int i=0;
    //To remove the first portion of request
    while(i<request.length() && request[i]!='.'){
        i++;
    }
    i++;
    start=i;
    
    while(i<request.length() && request[i]!='.'){
        current_serve+=request[i];
        i++;    
    }
    //separate name and value of tag
    std::string tag_name="";
    std::string tag_value="";
    bool is_value=false;
    for(int i{0};i<current_serve.length();i++){
        if(current_serve[i]=='['){
            is_value=true;
        }
        if(is_value==false){
            tag_name+=current_serve[i];
        }
        else if(is_value==true && current_serve[i]!='[' && current_serve[i]!=']'){
            tag_value+=current_serve[i];
        }
        
    }
    std::stringstream conversion_to_int(tag_value);
    conversion_to_int>>count;
    //search for that tag as many times given in tag_value
    for(int j{0};j<xml_data.tag_list.size();j++){
        
        if(xml_data.tag_list[j].tag==tag_name){
            count--;
        }
        if(count==-1){
            if(i==request.length()){
                return xml_data.tag_list[j].tag_list[0].tag;
            }
            return search_query(xml_data.tag_list[j],request.substr(start,request.length()-start));
        }
        
        
    }
    return "Not a valid query";
    
    
}
#endif