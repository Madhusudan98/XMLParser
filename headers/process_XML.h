#ifndef process_XML_h
#define process_XML_h

struct graph{
    std::string tag;
    std::vector<graph> tag_list;
};

std::vector<std::string> tag_list(std::string);
graph tag_separtor(std::string);

graph tag_separtor(std::string xml_str){
    std::string main_tag="";
    graph xml_graph;
    std::vector<std::string> tag_vector;
    if(xml_str[0]!='<'){
        if(xml_str.length()>=13 && xml_str.substr(0,13)=="__attribute__"){
            std::string attribute_tag="";
            std::string attribute_value="";
            bool is_value=false;
            for(int i{13};i<xml_str.length();i++){
                if(xml_str[i]=='='){
                    is_value=true;
                    continue;
                }
                if(is_value==false){
                    attribute_tag+=xml_str[i];
                }
                else if(is_value==true){
                    
                    attribute_value+=xml_str[i];
                }
            }
            xml_graph.tag=attribute_tag;
            std::string actual_value=attribute_value.substr(0,attribute_value.length());
            graph new_graph;
            new_graph.tag=actual_value;
            xml_graph.tag_list.push_back(new_graph);
            //std::cout<<actual_value<<"   "<<attribute_tag<<"  "<<attribute_tag.length()<<std::endl;
            return xml_graph;
        }
        
        xml_graph.tag=xml_str;
        return xml_graph;
    
    }
    else{
        int start;
        int end;
        for(int i{0};i<xml_str.length();i++){
            if(xml_str[i]=='>'){
                start=i+1;
                break;
            }
        }
        main_tag=xml_str.substr(1,start-2);
        xml_graph.tag=main_tag;
        
        std::string search_tag="</"+main_tag+">";
        int search_len=search_tag.length();
        while(isspace(xml_str[start]) && start<xml_str.length()){
            start++;
        }
        for(int i{start};i<xml_str.length();i++){
            if(xml_str.substr(i,search_len)==search_tag){
                end=i-1;
            }
        }
        while(isspace(xml_str[end]) && end>0){
            end--;
        }
        std::string new_xml_str=xml_str.substr(start,end-start+1);
        
        tag_vector=tag_list(new_xml_str);
    }
    
    
    for(auto c:tag_vector){
        xml_graph.tag_list.push_back(tag_separtor(c));
    }
    return xml_graph;
    
}



std::vector<std::string> tag_list(std::string xml_str){
    int start=0;
    int end;
    std::string closing_tag_sign="</";
    std::vector<std::string> tag_vector={};
    if(xml_str[0]!='<'){
        tag_vector.push_back(xml_str);
        return tag_vector;
    }
    std::string main_tag="";
    std::string search_tag="";
    int search_len;
    for(int i{0};i<xml_str.length();i++){
        loop_start:
        if(xml_str[i]=='<'){
            start=i;
            i++;
            while(i<xml_str.length() && xml_str[i]!='>'){
                if(xml_str[i]=='/' && i+1<xml_str.length() && xml_str[i+1]=='>'){
                    end=i+1;
                    std::string attribute_tag="__attribute__";
                    tag_vector.push_back(attribute_tag+xml_str.substr(start+1,end-start-2));
                    main_tag.clear();
                    i++;
                    goto loop_start;
                }
                main_tag+=xml_str[i];
                i++;
            }
            search_tag="</"+main_tag+">";
            search_len=search_tag.length();
            while(i+search_len<xml_str.length() && xml_str.substr(i,search_len)!=search_tag){
                i++;
            }
            end=i+search_len-1;
            tag_vector.push_back(xml_str.substr(start,end-start+1));
            main_tag.clear();
        }
    }
    return tag_vector;
}


#endif