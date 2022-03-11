#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<regex>
#include <sstream>
#include <fstream>
#include "headers/XMLCheck.h"
#include "headers/Update_XML.h"
#include "headers/process_XML.h"
#include "headers/search_XML.h"

void print_tags(graph xml_grpah,int nested_level){
    if(xml_grpah.tag_list.size()==0){
        return;
    }
    std::string indent="";
    for(int i{0};i<nested_level;i++){
        indent+="---";
    }
    
    std::cout<<indent<<xml_grpah.tag<<std::endl;
    for(int i{0};i<xml_grpah.tag_list.size();i++){
        print_tags(xml_grpah.tag_list[i],nested_level+1);
    }
    return;
}
bool compare_graph_tag(graph xml1, graph xml2){
    return xml1.tag<xml2.tag;
}


std::string printJSON(graph xml_graph,std::string indent,bool tag_already_present = false){
    if(xml_graph.tag_list.size()==0){
//        return  indent+"#text : {\"" +xml_graph.tag + "\"";
        return  indent + "\""+"text"+"\":\"" + xml_graph.tag + "\"";
    }
    if(xml_graph.is_attribute){
        xml_graph.tag_list[0].tag .erase(std::remove(xml_graph.tag_list[0].tag.begin(), xml_graph.tag_list[0].tag .end(), '\n       '), xml_graph.tag_list[0].tag .end());
         return indent +"  "+ "\"@"+xml_graph.tag + "\" : " + xml_graph.tag_list[0].tag + "";
    }
    if(xml_graph.tag_list.size()==1 && xml_graph.tag_list[0].tag_list.size()==0){
        xml_graph.tag_list[0].tag .erase(std::remove(xml_graph.tag_list[0].tag.begin(), xml_graph.tag_list[0].tag .end(), '\n       '), xml_graph.tag_list[0].tag .end());
        return indent +"  "+ "\""+xml_graph.tag + "\" : \"" + xml_graph.tag_list[0].tag + "\"";
    }
    else{
        //gets all the element which share the same key
        std::sort(xml_graph.tag_list.begin(),xml_graph.tag_list.end(), compare_graph_tag);
        std::map<std::string,int> tag_count;
        int n = xml_graph.tag_list.size();
        for(int i=0;i<n;i++){
            tag_count[xml_graph.tag_list[i].tag]++;
        }

        std::string currKey="";
        if(tag_already_present){
            currKey+="{\n";
        }
        else{
            currKey+= indent + "{\n\"" + xml_graph.tag + "\" : {\n";
        }
        indent+="  ";
        for(int i = 0;i<n;i++){
            if(tag_count[xml_graph.tag_list[i].tag]>1){
                std::string current_tag = xml_graph.tag_list[i].tag;
                currKey+= indent + indent+ "\"" + current_tag + "\" : ";
                currKey+="[";
                tag_count[xml_graph.tag_list[i].tag]--;
                while (xml_graph.tag_list[i].tag==current_tag){
                    bool tag_already_present = true;
                    std::string  temp_indent = "  ";
                    currKey += printJSON(xml_graph.tag_list[i],temp_indent,tag_already_present);
                    tag_count[xml_graph.tag_list[i].tag]--;
                    if(tag_count[xml_graph.tag_list[i].tag]>=0){
                        currKey+= ",\n";
                    }
                    i++;
                }
                i--;
                if(i!=xml_graph.tag_list.size()-1){
                    currKey+="],\n";
                }
                else{
                    currKey+="]\n";
                }
            }
            else{
                currKey+= "";
                currKey += printJSON(xml_graph.tag_list[i],indent);
                if(i!=xml_graph.tag_list.size()-1){
                    currKey+= ",\n";
                }
            }

        }
        currKey+="";
        currKey+=indent +" \n}";
        return  currKey;
    }
}


int main(){

    std::cout<<"Welcome to the XML Parser program"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Please Enter the path of your file, followed by its name"<<std::endl;
    std::string filename;
    
    
    char line;
    std::string xml_str="";
    //reads file from the file system
    std::getline(std::cin>> std::ws,filename);
    std::ifstream xml_document(filename);
    if(!xml_document){
        std::cout<<"File not found"<<std::endl;
        return 0;
    }
    else{
        while(xml_document.get(line)){
            xml_str+=line;
        }
        xml_document.close();
    }
    int start=0;
    //To skip lines like  - <?xml version="1.0" encoding="ISO-8859-1"?>  
    if(xml_str[0]=='<' && xml_str[1]=='?'){
        while(xml_str[start]!='>'){
            start++;
        }
        start++;
    }
    //remove the above mentioned xml metadata
    xml_str=xml_str.substr(start,xml_str.length()-start+1);
    std::smatch xml_start_match;
    std::regex reg ("(<[^<]*>)");
    //gets the starting of xml, skips whitespace or other rather chracters before xml actually starts
    std::regex_search(xml_str,xml_start_match,reg);
    start=xml_start_match.position();
    xml_str=xml_str.substr(start,xml_str.length()-start+1);
    graph xml_graph=tag_separtor(xml_str);
    if(check_xml(xml_str)==false){
        return 0;
    }
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Choose an action to perform"<<std::endl;
    std::string input;
    while(input!="6")
        {
        input.clear();
        std::cout<<"Enter the index number to perform action"<<std::endl;
        std::cout<<"1. Show all tags "<<std::endl;
        std::cout<<"2. Perform a Search Query"<<std::endl;
        std::cout<<"3. Update a value:"<<std::endl;
        std::cout<<"4. Add a new tag:"<<std::endl;
        std::cout<<"5. To see the XML File"<<std::endl;
        std::cout<<"6. Close the Program"<<std::endl;
        std::cin>>input;
        if(input=="1"){
//            print_tags(xml_graph,0);
            // std::cout<<"Calling printJSON func"<<std::endl;
            std::string xml_json = "{";
            std::string indent = "";
            xml_json = printJSON(xml_graph,indent);
            xml_json+="}";
            std::cout<<xml_json<<std::endl;
            std::cout<<std::endl;std::cout<<std::endl;std::cout<<std::endl;std::cout<<std::endl;std::cout<<std::endl;
        }
        else if(input=="2"){
            std::cout<<std::endl;
            std::cout<<"Give input in form of tag1[i].tag[j].tag3[k]"<<std::endl;
            std::string search_input;
            std::getline(std::cin>> std::ws,search_input);
            std::string query_output;
            query_output=search_query(xml_graph,search_input);
            std::cout<<query_output<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
        }
        else if(input=="3"){
            std::cout<<"1. To update an Element"<<std::endl;
            std::cout<<"2. To update an Attribute"<<std::endl;
            std::string element_attribute;
            std::cin>>element_attribute;
            std::cout<<"To update a value give input of position in form of tag1[i].tag[j].tag3[k]"<<std::endl;
            std::string position;
            std::getline(std::cin>> std::ws,position);
            std::cout<<"Enter the updated value"<<std::endl;
            std::string input_value;
            std::getline(std::cin>> std::ws,input_value);
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::string choice;
            if(element_attribute=="1"){
            update_xml(xml_str,input_value,position,true,false);
            }
            else if(element_attribute=="2") {
                update_xml(xml_str,input_value,position,true,true);
            }
            else{
                std::cout<<"incorrect input"<<std::endl;
            }
            std::cout<<"1. To see the update xml"<<std::endl;
            std::cout<<"0. Continue"<<std::endl;
            std::cin>>choice;
            if(choice=="1"){
                std::cout<<xml_str<<std::endl;
                std::cout<<std::endl;
                std::cout<<std::endl;
                std::cout<<std::endl;
            }
            std::cout<<"2. Save the changes"<<std::endl;
            std::cout<<"0. Continue"<<std::endl;
            choice.clear();
            std::cin>>choice;
            if(choice=="2"){
                std::ofstream out("updated"+filename);
               out << xml_str;
               out.close();
            }
        }
        else if(input=="4"){
            std::cout<<"To add a new tag give input of position in form of tag1[i].tag[j].tag3[k]"<<std::endl;
            std::string position;
            std::cin>>position;
            std::cout<<"Enter the tag"<<std::endl;
            std::string input_value;
            std::getline(std::cin>> std::ws,input_value);
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::string choice;
            update_xml(xml_str,input_value,position,false,false);
            std::cout<<"1. To see the update xml"<<std::endl;
            std::cout<<"0. Continue"<<std::endl;
            std::cin>>choice;
            if(choice=="1"){
                std::cout<<xml_str<<std::endl;
            }
            std::cout<<"2. Save the changes"<<std::endl;
            std::cout<<"0. Continue"<<std::endl;
            choice.clear();
            std::cin>>choice;
            if(choice=="2"){
                std::ofstream out("updated"+filename);
               out << xml_str;
               out.close();
        }
        }
        else if(input=="5"){
            std::cout<<std::endl;std::cout<<std::endl;
            std::cout<<xml_str<<std::endl;
            std::cout<<std::endl;std::cout<<std::endl;
        }
        else if(input=="6"){
            break;
        }
        else{
            std::cout<<"Wrong input, Please Try again"<<std::endl;
        }
        
    }
    
    
    
    return 0;
    
}
