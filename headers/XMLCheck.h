#ifndef _XMLParser_h
#define _XMLParser_h
#include "process_XML.h"

bool check_xml(std::string xml_str){
    std::string tag_name="";
    //a stack of tags which is used for xml validation
    std::stack<std::string> tag_stack;
    for(int i{0};i<xml_str.length();i++){
        if(xml_str[i]=='<'){
            int tag_start;
            int tag_end;
            tag_start=i;
            while(i<xml_str.length() && xml_str[i]!='>'){
                i++;
            }
            tag_end=i;
            //to check for the condition of self closing tags
            if(xml_str[tag_end-1]=='/'){
                continue;
            }
            else{
                std::string tag_string=xml_str.substr(tag_start,tag_end-tag_start+1);
                std::string main_tag=tag_name_separator(tag_string);
                if(tag_stack.empty()==false && tag_stack.top()==main_tag){
                    tag_stack.pop();
                }
                else{
                 tag_stack.push(main_tag);
                }
            }
        }
    }
    
    if(tag_stack.empty()==true){
        return true;
    }
    else{
        std::cout<<"invalid XML file"<<std::endl;
        return false;
    }
    
    
}


#endif