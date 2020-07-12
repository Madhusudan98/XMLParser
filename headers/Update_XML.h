#ifndef _Update_XML_h
#define _Update_XML_h


void update_xml(std::string &xml_str,std::string new_value,std::string position,bool update_tag,bool search_attribute){
    //position is in the form tag1[x].tag2[y].tag3[z]
    std::vector<std::string> search_tag;
    //divides the position into multiple part and store the first most component in current_tag
    std::string current_tag="";
    //remove first most component of the position
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
    //separte the name of tag(tag1) and the value([x]) and store it into different vectors
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
        tag_name_vector.push_back(tag_name);
        tag_value_vector.push_back((count+1)*2-1);
        
    }
    
    int position_index=0;
    std::string search_string="";
    int insert_point=0;
    count=0;
    bool inside_tagspace=false;
    if(search_attribute==true){
        //to check if we are searching withing <.....>
        
        for(int i{0};i<xml_str.length();i++){
            
            if(xml_str[i]=='<'){
                inside_tagspace=true;
            }
            if(xml_str[i]=='>'){
                inside_tagspace=false;
            }
            //checks if instance of search tag have been found
            if(xml_str.substr(i,tag_name_vector[position_index].length())==tag_name_vector[position_index] 
            && inside_tagspace){
                i+=xml_str.substr(i,tag_name_vector[position_index].length()).length();
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
        while(xml_str[insert_point]!='"'){
            insert_point++;
        }
        insert_point++;
        int attribute_value_end;
        int attribute_value_start=insert_point;
        while(xml_str[insert_point]!='"'){
            insert_point++;
        }
        xml_str.erase(attribute_value_start,insert_point-attribute_value_start);
        std::cout<<std::endl;std::cout<<std::endl;std::cout<<std::endl;std::cout<<std::endl;
        xml_str.insert(attribute_value_start,new_value);
        return;
        
    }
    
    std::cout<<std::endl;std::cout<<std::endl;
    for(int i{0};i<xml_str.length();i++){
        if(xml_str[i]=='<'){
            inside_tagspace=true;
        }
        if(xml_str[i]=='>'){
            inside_tagspace=false;
        }
        if(xml_str.substr(i,tag_name_vector[position_index].length())==tag_name_vector[position_index]
        && inside_tagspace){
            i+=tag_name_vector[position_index].length();
            count++;
            if(count==tag_value_vector[position_index]){
                count=0;
                position_index++;
                if(position_index==tag_name_vector.size()){
                    insert_point=i;
                    while(insert_point<xml_str.length() && xml_str[insert_point]!='>'){
                        insert_point++;
                    }
                    insert_point++;
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