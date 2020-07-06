#ifndef _Update_XML_h
#define _Update_XML_h


void update_xml(std::string &xml_str,std::string new_value,std::string position,bool update_tag){
    std::vector<std::string> search_tag;
    std::string current_tag="";
    for(int i{0};i<position.length();i++){
        if(position[i]=='.' || i==position.length()-1){
            if(i==position.length()-1){
                current_tag+=position[i];
            }
            search_tag.push_back(current_tag);
            current_tag.clear();
        }
        else{
            current_tag+=position[i];
        }
    }
    int count=0;
    std::string tag_name="";
    std::string tag_value="";
    std::vector<std::string> tag_name_vector;
    std::vector<int> tag_value_vector;
    bool is_value=false;
    for(auto c:search_tag){
        is_value=false;
        tag_value.clear();
        tag_name.clear();
        for(int i{0};i<c.length();i++){
            if(c[i]=='['){
                is_value=true;
            }
            if(is_value==false){
                tag_name+=c[i];
            }
            else if(is_value==true && c[i]!='[' && c[i]!=']'){
                tag_value+=c[i];
            }
            
        }
        std::stringstream conversion_to_int(tag_value);
        conversion_to_int>>count;
        tag_name_vector.push_back("<"+tag_name+">");
        tag_value_vector.push_back(count+1);
        
    }
    
    int position_index=0;
    std::string search_string="";
    int insert_point=0;
    count=0;
    for(int i{0};i<xml_str.length();i++){
        if(xml_str.substr(i,tag_name_vector[position_index].length())==tag_name_vector[position_index]){
            i+=tag_name_vector[position_index].length();
            count++;
            if(count==tag_value_vector[position_index]){
                count=0;
                position_index++;
                if(position_index==tag_name_vector.size()){
                    insert_point=i;


                    break;
                }
            }
        }
    }
    if(update_tag){
        int delete_len=0;
        int delete_end=insert_point;
        while(xml_str[delete_end]!='<'){
            delete_end++;
        }
        xml_str.erase(insert_point,delete_end-insert_point);
        xml_str.insert(insert_point,new_value);
    }
    else{
        xml_str.insert(insert_point,"\n"+new_value);
    }
}

#endif