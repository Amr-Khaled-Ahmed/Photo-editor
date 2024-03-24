# include <iostream>
# include <cctype>
# include <string>
# include<cctype>
# include <cstring>
# include <algorithm>
# include <vector>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <regex>
#include "Image_Class.h"


using namespace std;


void black_white(Image& primary, string &name);
void invert_image(Image& primary, string &name);
void rotate_image(Image& primary, string &name);
void grayscale_image(Image& primary, string &name);
void merge_image(Image& primary,string &name);
void lighten_darken_image(Image &primary, string&name);
void filter_choices(string filter_choice, Image& primary, string &name);
void resizing(Image& primary, string &name);
void filters_menu(Image & primary, string &name);
void asking_for_saving(Image& primary, string &name);
string valid_choice(string filter_choice);
string image_name_validate(string name);
string choice_load_save(string choice);


int main() {

    // welcome user and ask him to load the image via name and extension
    cout<<"Welcome to our image filters application"<<endl<<endl;
    cout<<"Load your image"<<endl;
    cout<<"Enter your image name with a correct extension"<<endl;
    cout<<".jpg or .bmp or .png or .jpeg: ";
    string image_name;
    getline(cin,image_name);
    Image primary;

    // make sure that the image is in the directory
    while(true){
        try{
            primary.loadNewImage(image_name);
            cout<<"Loaded successfully"<<endl;
            cout<<endl;
            break;

        }
        catch(const invalid_argument& e) {
            cout<<"Enter a correct image name with correct extension"<<endl;
            cout<<".jpg or .bmp or .png or .jpeg"<<endl;
            getline(cin,image_name);
        }
    }
    filters_menu(primary, image_name);




}


// function that calls filter function according to user's choice
void filter_choices(string filter_choice, Image& primary, string &name){
    if (filter_choice == "1") {
        grayscale_image(primary,name);
    }
    else if (filter_choice == "2") {
        black_white(primary,name);
    }
    else if (filter_choice == "3") {
        invert_image(primary,name);
    }
    else if(filter_choice=="4"){
        merge_image(primary,name);
    }
    else if (filter_choice == "6") {
        rotate_image(primary,name);
    }
    else if(filter_choice=="7"){
        lighten_darken_image(primary,name);
    }else if (filter_choice == "11"){
        resizing(primary, name);;
    }
    else if(filter_choice=="8"){
        cout<<"Thanks for using our image filters application"<<endl;
        exit(0);
    }
}

// function that validates filter_choice
string valid_choice(string filter_choice){
    while(true){
        if(filter_choice == "1")break;
        else if(filter_choice == "2")break;
        else if(filter_choice == "3")break;
        else if(filter_choice == "4")break;
        else if(filter_choice == "6")break;
        else if(filter_choice == "7")break;
        else if(filter_choice == "11")break;
        else if(filter_choice == "16"){
            cout<<"Thanks for using our image filter application"<<endl;
            exit(0);
        }
        else{
            cout<<"Please enter a valid choice"<<endl;
            cin>>filter_choice;
        }
    }
    return filter_choice;
}

// function that validates if entered image name has a correct extension
string image_name_validate(string name){

    while(true){
        if(name.length()-4 >0 && name[name.length()-1]=='p' && name[name.length()-2]=='m' && name[name.length()-3]=='b' && name[name.length()-4]=='.'){
            return name;
        }
        else if(name.length()-4 >0  &&name[name.length()-1]=='g' && name[name.length()-2]=='p' && name[name.length()-3]=='j' && name[name.length()-4]=='.'){
            return name;
        }
        else if(name.length()-4 >0  &&name[name.length()-1]=='g' && name[name.length()-2]=='n' && name[name.length()-3]=='p' && name[name.length()-4]=='.'){
            return name;
        }
        else if(name.length()-5 >0  &&name[name.length()-1]=='g' && name[name.length()-2]=='e' && name[name.length()-3]=='p' && name[name.length()-4]=='j' && name[name.length()-5]=='.'){
            return name;
        }
        else{
            cout<<"Please enter a correct name with a correct extension: "<<endl;
            cin>>name;
            return image_name_validate(name);
        }
    }

}

void filters_menu(Image & primary, string &name){
    // print out filter options for user
    cout<<"1. Grayscale"<<endl;
    cout<<"2. Black and White filter" << endl;
    cout<<"3. Invert image"<<endl;
    cout<<"4. Merge two images"<<endl;
    cout<<"6. Rotate image"<<endl;
    cout<<"7. Darken and Lighten Image"<<endl;
    cout<<"11. resizing"<<endl;

    cout<<"16. Exit"<<endl<<endl;
    cout<<"Please enter your filter choice: "<<endl;
    string filter_choice;
    cin>>filter_choice;

    // validate filter choice and do the filter according to the choice of the user
    filter_choice=valid_choice(filter_choice);
    filter_choices(filter_choice,primary,name);
}

// function that validates load or save choice
string choice_load_save(string choice){
    while(true){
        if(choice=="1")return choice;
        else if(choice=="2")return choice;
        else{
            cout<<"Please enter a correct choice: "<<endl;
            cin>>choice;
        }
    }
}



void invert_image(Image& primary, string &name) {
    for (int i = 0; i < primary.width; i++) {
        for (int j = 0; j < primary.height; j++) {
            for (int k = 0; k < primary.channels; k++) {
                primary(i, j, k) = 255 - primary(i, j, k);
            }
        }
    }
    asking_for_saving(primary, name);
}


void rotate_image( Image& primary, string &name) {
    Image rotated_image(primary.height, primary.width); // declare this photo to 90 degree's photo
    char x,y;
    cout<<"1: rotate by 90 degree\n";
    cout<<"2: rotate by 180 degree\n";
    cout<<"3: rotate by 270 degree\n";
    cout<<"Enter your choice between 1&2&3: ";
    cin>>x;
    while(x!='1'&&x!='2'&&x!='3'){
        cout<<"invalid choice\n";
        cout<<"Enter your choice between 1&2&3: ";
        cin>>x;
    }
    cout<<"1: begin rotation from right: \n";
    cout<<"2: begin rotation from left: \n";
    cout<<"Choose between 1&2: ";
    cin>>y;
    while(y!='1'&&y!='2'){
        cout<<"invalid choice\n";
        cout<<"1: begin rotation from left: \n";
        cout<<"2: begin rotation from right: \n";
        cout<<"Choose between 1&2: ";
        cin>>y;
    }
    if(y=='1'){ // check to begin from left
        if(x=='1'){
            for (int i = 0; i < primary.width; i++) {
                for (int j = 0; j < primary.height; j++) {
                    rotated_image(j, primary.width - 1 - i, 0) = primary(i, j, 0); //j represents the row index || primary.width - 1 - i represents the new column index on matrix for red color
                    rotated_image(j, primary.width - 1 - i, 1) = primary(i, j, 1); //j represents the row index || primary.width - 1 - i represents the new column index on matrix for green color
                    rotated_image(j, primary.width - 1 - i, 2) = primary(i, j, 2); //j represents the row index || primary.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            asking_for_saving(rotated_image, name);
        }
        else if (x == '2') {
            for (int i = 0; i < primary.width; i++) {
                for (int j = 0; j < primary.height; j++) {
                    rotated_image(j, primary.width - 1 - i, 0) = primary(i, j, 0); //j represents the row index || primary.width - 1 - i represents the new column on matrix for red color
                    rotated_image(j, primary.width - 1 - i, 1) = primary(i, j, 1); //j represents the row index || primary.width - 1 - i represents the new column on matrix for green color
                    rotated_image(j, primary.width - 1 - i, 2) = primary(i, j, 2); //j represents the row index || primary.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            Image rotated_image_2(rotated_image.height, rotated_image.width); // declare this photo that will be 180 degree's photo
            for (int i = 0; i < rotated_image.width; i++) {
                for (int j = 0; j < rotated_image.height; j++) {
                    rotated_image_2(j, rotated_image.width - 1 - i, 0) = rotated_image(i, j, 0); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for red color
                    rotated_image_2(j, rotated_image.width - 1 - i, 1) = rotated_image(i, j, 1); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for green color
                    rotated_image_2(j, rotated_image.width - 1 - i, 2) = rotated_image(i, j, 2); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for blue color
                }
            }

            asking_for_saving(rotated_image_2, name);
        }
        else if(x=='3'){
            for (int i = 0; i < primary.width; i++) {
                for (int j = 0; j < primary.height; j++) {
                    rotated_image(j, primary.width - 1 - i, 0) = primary(i, j, 0);  //j represents the row index || primary.width - 1 - i represents the new column index on matrix for red color
                    rotated_image(j, primary.width - 1 - i, 1) = primary(i, j, 1);  //j represents the row index || primary.width - 1 - i represents the new column index on matrix for green color
                    rotated_image(j, primary.width - 1 - i, 2) = primary(i, j, 2);  //j represents the row index || primary.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            Image rotated_image_2(rotated_image.height, rotated_image.width);
            for (int i = 0; i < rotated_image.width; i++) {
                for (int j = 0; j < rotated_image.height; j++) {
                    rotated_image_2(j, rotated_image.width - 1 - i, 0) = rotated_image(i, j, 0); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for red color
                    rotated_image_2(j, rotated_image.width - 1 - i, 1) = rotated_image(i, j, 1); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for green color
                    rotated_image_2(j, rotated_image.width - 1 - i, 2) = rotated_image(i, j, 2); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            Image rotated_image_3(rotated_image_2.height, rotated_image_2.width); // declare this photo that will be 270 degree's photo
            for (int i = 0; i < rotated_image_2.width; i++) {
                for (int j = 0; j < rotated_image_2.height; j++) {
                    rotated_image_3(j, rotated_image_2.width - 1 - i, 0) = rotated_image_2(i, j, 0); //j represents the row index || rotated_image_2.width - 1 - i represents the new column index on matrix for red color
                    rotated_image_3(j, rotated_image_2.width - 1 - i, 1) = rotated_image_2(i, j, 1); //j represents the row index || rotated_image_2.width - 1 - i represents the new column index on matrix for green color
                    rotated_image_3(j, rotated_image_2.width - 1 - i, 2) = rotated_image_2(i, j, 2); //j represents the row index || rotated_image_2.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            asking_for_saving(rotated_image_3, name);
        }
    }
    if(y=='2'){ // check to begin from right
        if(x=='1'){
            for (int i = 0; i < primary.width; i++) {
                for (int j = 0; j < primary.height; j++) {
                    rotated_image(j, primary.width - 1 - i, 0) = primary(i, j, 0);  //j represents the row index || primary.width - 1 - i represents the new column index on matrix for red color
                    rotated_image(j, primary.width - 1 - i, 1) = primary(i, j, 1);  //j represents the row index || primary.width - 1 - i represents the new column index on matrix for green color
                    rotated_image(j, primary.width - 1 - i, 2) = primary(i, j, 2);  //j represents the row index || primary.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            Image rotated_image_2(rotated_image.height, rotated_image.width);
            for (int i = 0; i < rotated_image.width; i++) {
                for (int j = 0; j < rotated_image.height; j++) {
                    rotated_image_2(j, rotated_image.width - 1 - i, 0) = rotated_image(i, j, 0); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for red color
                    rotated_image_2(j, rotated_image.width - 1 - i, 1) = rotated_image(i, j, 1); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for green color
                    rotated_image_2(j, rotated_image.width - 1 - i, 2) = rotated_image(i, j, 2); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            Image rotated_image_3(rotated_image_2.height, rotated_image_2.width); // declare this photo that will be 270 degree's photo
            for (int i = 0; i < rotated_image_2.width; i++) {
                for (int j = 0; j < rotated_image_2.height; j++) {
                    rotated_image_3(j, rotated_image_2.width - 1 - i, 0) = rotated_image_2(i, j, 0); //j represents the row index || rotated_image_2.width - 1 - i represents the new column index on matrix for red color
                    rotated_image_3(j, rotated_image_2.width - 1 - i, 1) = rotated_image_2(i, j, 1); //j represents the row index || rotated_image_2.width - 1 - i represents the new column index on matrix for green color
                    rotated_image_3(j, rotated_image_2.width - 1 - i, 2) = rotated_image_2(i, j, 2); //j represents the row index || rotated_image_2.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            asking_for_saving(rotated_image_3, name);
        }
        if(x=='2'){
            for (int i = 0; i < primary.width; i++) {
                for (int j = 0; j < primary.height; j++) {
                    rotated_image(j, primary.width - 1 - i, 0) = primary(i, j, 0); //j represents the row index || primary.width - 1 - i represents the new column on matrix for red color
                    rotated_image(j, primary.width - 1 - i, 1) = primary(i, j, 1); //j represents the row index || primary.width - 1 - i represents the new column on matrix for green color
                    rotated_image(j, primary.width - 1 - i, 2) = primary(i, j, 2); //j represents the row index || primary.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            Image rotated_image_2(rotated_image.height, rotated_image.width); // declare this photo that will be 180 degree's photo
            for (int i = 0; i < rotated_image.width; i++) {
                for (int j = 0; j < rotated_image.height; j++) {
                    rotated_image_2(j, rotated_image.width - 1 - i, 0) = rotated_image(i, j, 0); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for red color
                    rotated_image_2(j, rotated_image.width - 1 - i, 1) = rotated_image(i, j, 1); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for green color
                    rotated_image_2(j, rotated_image.width - 1 - i, 2) = rotated_image(i, j, 2); //j represents the row index || rotated_image.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            asking_for_saving(rotated_image_2, name);
        }
        if(x=='3'){
            for (int i = 0; i < primary.width; i++) {
                for (int j = 0; j < primary.height; j++) {
                    rotated_image(j, primary.width - 1 - i, 0) = primary(i, j, 0); //j represents the row index || primary.width - 1 - i represents the new column index on matrix for red color
                    rotated_image(j, primary.width - 1 - i, 1) = primary(i, j, 1); //j represents the row index || primary.width - 1 - i represents the new column index on matrix for green color
                    rotated_image(j, primary.width - 1 - i, 2) = primary(i, j, 2); //j represents the row index || primary.width - 1 - i represents the new column index on matrix for blue color
                }
            }
            asking_for_saving(rotated_image, name);
        }
    }
}
void merge_image(Image& primary,string &name){
    cin.ignore();
    cout<<"Please load your second image"<<endl;
    cout<<"Enter your image name with a correct extension"<<endl;
    cout<<".jpg or .bmp or .png or .jpeg: ";
    string image_name;
    getline(cin,image_name);
    Image secondary;
    // make sure that the image is in the directory
    while(true){
        try{
            secondary.loadNewImage(image_name);
            cout<<"Loaded successfully"<<endl;
            cout<<endl;
            break;

        }
        catch(const invalid_argument& e) {
            cout<<"Enter a correct image name with correct extension"<<endl;
            cout<<".jpg or .bmp or .png or .jpeg"<<endl;
            getline(cin,image_name);
        }
    }
//    Image thirdly(primary.width,primary.height);
//    for(int i=0; i<thirdly.width; i++) {
//        for (int j = 0; j < thirdly.height; i++) {
//            for (int k = 0; k < thirdly.channels; k++) {
//                thirdly(i, j, k) = 255;
//            }
//        }
//    }
    for(int i=0; i< primary.width; i++){
        for(int j=0; j<primary.height; j++){
            if(secondary(i,j,0)>primary(i,j,0)){
                primary(i,j,0)=secondary(i,j,0)-primary(i,j,0);
            }
            else if(primary(i,j,0)>=secondary(i,j,0)){
                primary(i,j,0)=primary(i,j,0)-secondary(i,j,0);
            }
            if(secondary(i,j,1)>primary(i,j,1)){
                primary(i,j,1)=secondary(i,j,1)-primary(i,j,1);
            }
            else if(primary(i,j,1)>=secondary(i,j,1)){
                primary(i,j,1)=primary(i,j,1)-secondary(i,j,1);
            }
            if(secondary(i,j,2)>primary(i,j,2)){
                primary(i,j,2)=secondary(i,j,2)-primary(i,j,2);
            }
            else if(primary(i,j,2)>=secondary(i,j,2)){
                primary(i,j,2)=primary(i,j,2)-secondary(i,j,2);
            }



        }



    }
    primary.saveImage("name.jpg");

}

void lighten_darken_image(Image &primary, string&name){
    cout<<"1. Lighten Image"<<endl;
    cout<<"2. Darken Image"<<endl;
    cout<<"Enter 1 or 2"<<endl;
    string filter_choice;
    cin>>filter_choice;
    filter_choice=choice_load_save(filter_choice);
    if(filter_choice=="1"){
        for(int i=0; i<primary.width; i++){
            for(int j=0; j<primary.height; j++){
                for(int k=0; k<primary.channels; k++){
                    if(primary(i,j,k)+primary(i,j,k)/2>255){
                        primary(i,j,k)=255;
                    }
                    else{
                        primary(i,j,k)+=primary(i,j,k)/2;
                    }
                }
            }
        }
    }
    else if(filter_choice=="2"){
        for(int i=0; i<primary.width; i++){
            for(int j=0; j<primary.height; j++){
                for(int k=0; k<primary.channels; k++){
                    primary(i,j,k)-=primary(i,j,k)/2;
                }
            }
        }
    }
    asking_for_saving(primary, name);

}

void grayscale_image(Image& primary, string &name){
    // loop on each pixel, calculate average of RGB and make each pixel equal that average
    for(int i=0; i<primary.width; i++){
        for(int j=0; j<primary.height; j++){
            unsigned int avg=0;
            avg+=primary(i,j,0);
            avg+=primary(i,j,1);
            avg+=primary(i,j,2);
            avg=avg/3;
            primary(i,j,0)=avg;
            primary(i,j,1)=avg;
            primary(i,j,2)=avg;
        }
    }

    asking_for_saving(primary, name);

}


void black_white(Image& primary, string &name){
    // if the pixel channel color was under 127 make it 0 else make it 255
    int avg = 0;
    for(int i=0; i<primary.width; i++){
        for(int j=0; j<primary.height; j++){
            for (int k = 0 ; k < primary.channels ; k++){
                avg =+ primary(i,j,k);
            }
            avg = avg%256;
            if(avg > 128){
                primary(i,j,0) = 255;
                primary(i,j,1) = 255;
                primary(i,j,2) = 255;

            }else{
                primary(i,j,0) = 0;
                primary(i,j,1) = 0;
                primary(i,j,2) = 0;

            }
        }
    }

    asking_for_saving(primary, name);

}


void resizing(Image& primary, string &name){
    /*
     * 1 --> declare a new image to store the old after resize
     * 2 --> declare pattern to validate on it
     * 3 --> declare matches to get the height and the width individually then turn them into integer
     * 4 --> get the width scale and the height scale by the old image height and width
     * 5 --> resize
     * */


// Declare variables for the scale and dimensions
    string scale;
    int ht, wd;
    smatch matches;

// Define a regex pattern for matching the scale format (width*height)
    regex pattern(R"((\d+)[*](\d+))");

// Declare variables for the width and height scale factors
    int width_scale, height_scale;

// Use a do-while loop to repeatedly prompt the user for input until a valid scale is entered
    do {
        // Prompt the user to enter the scale
        cout << "Enter the size you want in (format: width*height): ";
        cin.ignore();
        getline(cin, scale);

        // Check if the input matches the regex pattern
        if (!regex_search(scale, matches, pattern)) {
            // If the input does not match the pattern, print an error message and continue the loop
            cout << "Invalid input format" << endl;
            continue;
        }

        // Extract the width and height substrings from the input
        regex_search(scale, matches, pattern);
        string width_str = matches.str(1);
        string height_str = matches.str(2);

        // Convert the width and height substrings to integers
        width_scale = stoi(width_str);
        height_scale = stoi(height_str);

        // Check if the width and height scale factors are positive integers
        if (width_scale <= 0 || height_scale <= 0) {
            // If the width or height scale factor is not a positive integer, print an error message
            cout << "Invalid input: width and height must be positive integers" << endl;
        }

// Continue the loop until a valid scale is entered
    } while (!regex_search(scale, matches, pattern) || width_scale <= 0 || height_scale <= 0);

    // declare the resizing variables
    double h = (height_scale/1.0)/(primary.height/1.0) ,w = (width_scale/1.0)/(primary.width/1.0);

    // get the new image depend on the scale input
    Image after ( width_scale, height_scale);

    // this loop use to get the new image by resizing the old one
    for(int i = 0 ; i < after.width ; i++){
        for(int j = 0 ; j < after.height ; j++){
            after(i,j,0) = primary(i/w,j/h,0);
            after(i,j,1) = primary(i/w,j/h,1);
            after(i,j,2) = primary(i/w,j/h,2);

        }
    }


    asking_for_saving(after, name);
}

void asking_for_saving(Image& primary, string &name){
    // see if user wants to keep filtering or save the image
    cout<<"Press 1 if you want to save the image: "<<endl;
    cout<<"Press 2 if you want to continue filtering image: "<<endl;
    string choice;
    cin>>choice;
    choice=choice_load_save(choice);

    if(choice=="1"){
        cout<<"1. Save Image in same file"<<endl;
        cout<<"2. Save Image in new file"<<endl;
        cout<<"Enter 1 or 2"<<endl;
        string choice_1;
        cin>>choice_1;
        choice_1= choice_load_save(choice_1);
        // save in same file
        if(choice_1=="1"){
            primary.saveImage(name);
            cout<<"Saved Successfully"<<endl;
        }
            // save in new file
        else if(choice_1=="2"){
            cout<<"Enter your new image name with correct extension"<<endl;
            cout<<".jpg or .bmp or .png or .jpeg: ";
            string Image_name;
            cin>>Image_name;
            Image_name=image_name_validate(Image_name);
            primary.saveImage(Image_name);
            cout<<"Saved Successfully"<<endl<<endl;
        }
        cout<<endl<<endl;

        // see if user wants to continue using application
        cout<<"Press 1 if you want to load a new image"<<endl;
        cout<<"Press 2 if you want to exit"<<endl;
        string choice_2;
        cin>>choice_2;
        choice_2=choice_load_save(choice_2);
        if(choice_2=="1"){
            cin.ignore();
            main();
        }
        else if(choice_2=="2"){
            cout<<"Thanks for using our image filter application"<<endl;
            exit(0);
        }
    }

        // keep filtering
    else{
        filters_menu(primary,name);
    }
}