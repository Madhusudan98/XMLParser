#ifndef _XMLParser_h
#define _XMLParser_h

std::vector<std::string> check_xml(std::string xml_doc){
    std::string tag_name="";
    std::vector<std::string> tag_dir={};
    std::stack<std::string> tag_stack;
    for(int i{0};i<xml_doc.length();i++){
        loop_start:
        if(isspace(xml_doc[i])){
            continue;
        }
        
        if(xml_doc[i]=='<'){
            
            while(xml_doc[i]!='>'){
                if(xml_doc[i]=='/' && i+1<xml_doc.length() && xml_doc[i+1]=='>'){
                    std::string new_tag_name="";
                    for(int i{0};i<tag_name.length();i++){
                        if(tag_name[i]=='='){
                            break;
                        }
                        new_tag_name+=tag_name[i];
                    }
                    //std::cout<<new_tag_name<<std::endl;
                    tag_dir.push_back(new_tag_name);
                    tag_dir.push_back(new_tag_name);
                    tag_name.clear();
                    i++;
                    goto loop_start;
                }
                i++;
                if(xml_doc[i]!='/' && xml_doc[i]!='>'){
                    tag_name+=xml_doc[i];
                }
            }
            
            if(tag_stack.empty()==false && tag_stack.top()==tag_name){
                tag_stack.pop();
                tag_dir.push_back(tag_name);

            }
            else{
             tag_stack.push(tag_name);
             tag_dir.push_back(tag_name);
            }
            
            tag_name.clear();
        }
    }
    
    if(tag_stack.empty()==true){
        return tag_dir;
    }
    else{
        std::cout<<"invalid XML file"<<std::endl;
        std::vector<std::string> null_vector;
        return null_vector;
    }
    
    
}

void print_tags(std::vector<std::string> tag_dir){
    std::map<std::string,int> count_map;
    std::string whitespace="   ";
    for(int i{0};i<tag_dir.size()-1;i++){
        if(count_map.find(tag_dir[i])==count_map.end()){
            std::cout<<whitespace+tag_dir[i]<<std::endl;
            whitespace+="   ";
            count_map[tag_dir[i]]=0;
        }
        else{
            whitespace=whitespace.substr(0,whitespace.length()-3);
            count_map.erase(tag_dir[i]);
            
        }
        
    }
}
#endif