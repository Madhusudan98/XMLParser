#include<bits/stdc++.h>
#include "XMLCheck.h"
#include "Update_XML.h"
#include "process_XML.h"
#include "search_XML.h"
 


int main(){
    
    std::cout<<"Welcome to the XML Parser program"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"Please Enter the path of your file, followed by its name"<<std::endl;
    std::string filename;
    
    
    char line;
    std::string xml_str="";
    std::getline(std::cin>> std::ws,filename);
    std::ifstream xml_doc(filename);
    if(!xml_doc){
        std::cout<<"File not found"<<std::endl;
    }
    else{
        while(xml_doc.get(line)){
            xml_str+=line;
        }
        xml_doc.close();
    }
    int start=1;
    if(xml_str[0]=='<' && xml_str[1]=='?'){
        while(xml_str[start]!='<'){
            start++;
        }
    }
    xml_str=xml_str.substr(start-1,xml_str.length()-start+1);
    std::vector<std::string> tag_vector=check_xml(xml_str);
    if(tag_vector.size()==0){
        return 0;
    }
    graph xml_graph=tag_separtor(xml_str);
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
            print_tags(tag_vector);
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
            std::cout<<"To update a value give input of position in form of tag1[i].tag[j].tag3[k]"<<std::endl;
            std::string position;
            std::getline(std::cin>> std::ws,position);
            std::cout<<"Enter the updated value"<<std::endl;
            std::string input_value;
            std::getline(std::cin>> std::ws,input_value);
            std::cout<<std::endl;
            std::cout<<std::endl;
            std::string choice;
            update_xml(xml_str,input_value,position,true);
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
                std::ofstream out(filename);
                out<<xml_str;
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
            update_xml(xml_str,input_value,position,false);
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
                std::ofstream out(filename);
                out<<xml_str;
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