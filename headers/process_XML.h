#ifndef process_XML_h
#define process_XML_h

struct graph{
    std::string tag;
    std::vector<graph> tag_list;
};


std::vector<std::string> tag_list(std::string);
graph tag_separtor(std::string);
std::string tag_name_separator(std::string);
graph to_graph_object(std::string);



graph to_graph_object(std::string opening_tag){
    graph xml_graph;
    std::smatch matches;
    std::regex reg_tag_name("<(\\w+)/?>?");
    regex_search(opening_tag,matches,reg_tag_name);
    std::string tag_name=matches.str().substr(1,matches.str().length()-1);
    int len=opening_tag.length();
    if(opening_tag.substr(len-2,2)=="/>"){
        tag_name="__selfClosingTag__"+tag_name;
    }
    if(tag_name[tag_name.length()-1]=='>'){
        tag_name=tag_name.substr(0,tag_name.length()-1);
    }
    xml_graph.tag=tag_name;
    std::regex reg_attribute("(\\w+)=([\\w\"]+)");
    while(regex_search(opening_tag,matches,reg_attribute)){
        graph attribute_name_graph;
        graph attribute_value_graph;
        attribute_name_graph.tag=matches[1].str();
        
        attribute_value_graph.tag=matches[2].str();
        attribute_name_graph.tag_list.push_back(attribute_value_graph);
        xml_graph.tag_list.push_back(attribute_name_graph);
        opening_tag=matches.suffix().str();
    }
    return xml_graph;
}


std::string tag_name_separator(std::string opening_tag){
    std::smatch matches;
    std::regex reg_tag_name("</?(\\w+)");
    regex_search(opening_tag,matches,reg_tag_name);
    std::string tag_name;
    if(matches.str()[1]=='/'){
     tag_name=matches.str().substr(2,matches.str().length()-1);   
    }
    else{
    tag_name=matches.str().substr(1,matches.str().length()-1);
    }
    return tag_name;
}

graph tag_separtor(std::string xml_str){
    std::string main_tag="";
    graph xml_graph;
    std::vector<std::string> tag_vector;
    if(xml_str[0]!='<'){
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
        main_tag=xml_str.substr(0,start);
        xml_graph=to_graph_object(main_tag);
        if(xml_graph.tag.substr(0,18)=="__selfClosingTag__"){
            xml_graph.tag=xml_graph.tag.substr(18,xml_graph.tag.length()-18);
            return xml_graph;
        }
        std::string search_tag="</"+xml_graph.tag+">";
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
    std::vector<std::string> child_vector={};
    if(xml_str[0]!='<'){
        child_vector.push_back(xml_str);
        return child_vector;
    }
    std::string main_tag="";
    std::string search_tag="";
    int search_len;
    for(int i{0};i<xml_str.length();i++){
        std::string main_tag="";
        int start=0;
        int end=0;
        
        if(xml_str[i]=='<'){
            start=i;
            i++;
            while(xml_str[i]!='>'){
                i++;
            }
            end=i;
            if(xml_str[end-1]=='/'){
                std::string child=xml_str.substr(start,end-start+1);
                child_vector.push_back(child);
                i++;
                continue;
            }
            main_tag=tag_name_separator(xml_str.substr(start,end-start+1));
            search_tag="</"+main_tag+">";
            search_len=search_tag.length();
            while(i+search_len<xml_str.length() && xml_str.substr(i,search_len)!=search_tag){
                i++;
            }
            end=i+search_len-1;
            child_vector.push_back(xml_str.substr(start,end-start+1));
            main_tag.clear();
        }
    }
    return child_vector;
}


#endif