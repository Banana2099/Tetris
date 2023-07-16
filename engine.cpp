#include "headers/engine.hpp"

int engine::m_row1 = 0;
int engine::m_col1 = 0;
int engine::m_row2 = 0;
int engine::m_col2 = 0;
int engine::m_row3 = 0;
int engine::m_col3 = 0; 
int engine::m_row4 = 0; 
int engine::m_col4 = 0;

int engine::color_n = rand() % 6 + 1;
int engine::cube_shape = rand() % 7;
int engine::second_cube = rand() % 7;
int engine::rotate_ind = 0;

void engine::check_rotation(int y1,int x1, int y2,int x2, int y3,int x3, int y4,int x4){ 
    bool check{true};
    size_t width {matrix.at(0).size()};
    int d_ind{};

    for(int i = 0; i < 2; i++){
        //near wall shift 
        if(x1<0 || x2 <0 || x3<0 || x4<0){
            x1 +=1;     x2 +=1;     x3 +=1;   x4 +=1; 
        }
        else if(x1>= width|| x2 >=width || x3>=width || x4>=width){   
            x1 -=1;     x2 -=1;     x3 -=1;    x4 -=1; 
        }
        //near cube shift
        else{
            std::vector<int> temp_w{x1,x2,x3,x4}, act_w{m_col1,m_col2,m_col3,m_col4};
            d_ind =*std::max_element(act_w.begin(),act_w.end())- *std::max_element(temp_w.begin(),temp_w.end());
            d_ind = (d_ind==0)? *std::min_element(act_w.begin(),act_w.end())- *std::min_element(temp_w.begin(),temp_w.end()):d_ind;
            if(check && (matrix.at(y1).at(x1) != 0 || matrix.at(y2).at(x2) != 0 ||
                matrix.at(y3).at(x3) != 0 ||matrix.at(y4).at(x4) != 0)){
                    x1 +=d_ind;  x2 +=d_ind;  x3 +=d_ind;    x4 +=d_ind; 
            } 
            if(x1<0 || x2 <0 || x3<0 || x4<0 ||x1>= width|| x2 >=width || x3>=width || x4>=width)
                check=false;
        }
    }

    //hit cube
    if(check && (matrix.at(y1).at(x1) != 0 || matrix.at(y2).at(x2) != 0 ||
        matrix.at(y3).at(x3) != 0 ||matrix.at(y4).at(x4) != 0))
        check = false; 

    if(check){
        m_row1 = y1; m_col1 = x1;
        m_row2 = y2; m_col2 = x2;
        m_row3 = y3; m_col3 = x3;
        m_row4 = y4; m_col4 = x4; 
        rotate_ind++;
    }        
    rotate_ind = (rotate_ind > 3)? 0:rotate_ind;
}
        
void engine::rotation(char r){
    if(r != ' '){
        switch(cube_shape){
            case 0:
                if(rotate_ind == 0){check_rotation(m_row1,m_col1,m_row2,m_col2,m_row3-1,m_col3-1,m_row4,m_col4);}
                else if(rotate_ind == 1){check_rotation(m_row1,m_col1,m_row2,m_col2,m_row3+1,m_col3+1,m_row4,m_col4-2);}
                else if(rotate_ind == 2){check_rotation(m_row1+1,m_col1-1,m_row2,m_col2,m_row3,m_col3,m_row4,m_col4+2);}
                else if(rotate_ind == 3){check_rotation(m_row1-1,m_col1+1,m_row2,m_col2,m_row3,m_col3,m_row4,m_col4);}
                break;//T
            case 1:
                if(rotate_ind == 0){check_rotation(m_row1+1,m_col1-1,m_row2,m_col2,m_row3-1,m_col3+1,m_row4-2,m_col4+0);}
                else if(rotate_ind == 1){check_rotation(m_row1-1,m_col1+1,m_row2,m_col2,m_row3+1,m_col3-1,m_row4+0,m_col4-2);}
                else if(rotate_ind == 2){check_rotation(m_row1+1,m_col1-1,m_row2,m_col2,m_row3-0,m_col3-1,m_row4+1,m_col4+2);}
                else if(rotate_ind == 3){check_rotation(m_row1-1,m_col1+1,m_row2,m_col2,m_row3-0,m_col3+1,m_row4+1,m_col4+0);}
                break;//L
            case 2:
                if(rotate_ind == 0){check_rotation(m_row1+1,m_col1-1,m_row2,m_col2,m_row3-1,m_col3+1,m_row4+0,m_col4+2);}
                else if(rotate_ind == 1){check_rotation(m_row1-1,m_col1+1,m_row2,m_col2,m_row3+1,m_col3-1,m_row4-2,m_col4-0);}
                else if(rotate_ind == 2){check_rotation(m_row1+0,m_col1-1,m_row2,m_col2,m_row3-1,m_col3-1,m_row4+1,m_col4+0);}
                else if(rotate_ind == 3){check_rotation(m_row1-0,m_col1+1,m_row2,m_col2,m_row3+1,m_col3+1,m_row4+1,m_col4-2);}
                break;//rL
            case 3:
                if(rotate_ind == 0){check_rotation(m_row1+2,m_col1,m_row2,m_col2,m_row3,m_col3,m_row4,m_col4+2);}
                else if(rotate_ind == 1){check_rotation(m_row1-2,m_col1,m_row2,m_col2,m_row3,m_col3,m_row4,m_col4-2);}
                else if(rotate_ind == 2){check_rotation(m_row1+2,m_col1,m_row2,m_col2,m_row3,m_col3,m_row4,m_col4+2);}
                else if(rotate_ind == 3){check_rotation(m_row1-2,m_col1,m_row2,m_col2,m_row3,m_col3,m_row4,m_col4-2);}
                break;//Z
            case 4:
                if(rotate_ind == 0){check_rotation(m_row1+2,m_col1,m_row2,m_col2+2,m_row3,m_col3,m_row4,m_col4);}
                else if(rotate_ind == 1){check_rotation(m_row1-2,m_col1,m_row2,m_col2-2,m_row3,m_col3,m_row4,m_col4);}
                else if(rotate_ind == 2){check_rotation(m_row1+2,m_col1,m_row2,m_col2+2,m_row3,m_col3,m_row4,m_col4);}
                else if(rotate_ind == 3){check_rotation(m_row1-2,m_col1,m_row2,m_col2-2,m_row3,m_col3,m_row4,m_col4);}
                break;//rZ
            case 5:break;//O
            case 6:
                if(rotate_ind == 0){check_rotation(m_row1+2,m_col1-1,m_row2+1,m_col2+1,m_row3,m_col3,m_row4-1,m_col4+2);}
                else if(rotate_ind == 1){check_rotation(m_row1-2,m_col1+1,m_row2-1,m_col2-1,m_row3,m_col3,m_row4+1,m_col4-2);}
                else if(rotate_ind == 2){check_rotation(m_row1+2,m_col1-1,m_row2+1,m_col2+1,m_row3,m_col3,m_row4-1,m_col4+2);}
                else if(rotate_ind == 3){check_rotation(m_row1-2,m_col1+1,m_row2-1,m_col2-1,m_row3,m_col3,m_row4+1,m_col4-2);}
                break;//I
            default: break;
        }
    }
}        

bool engine::check_game(){
    bool check{false};
    for(int col = 0; col < matrix.at(0).size(); col++){
        if(matrix.at(buffer-1).at(col)>0)
            check = true;
    }
    return check;
}        

long engine::check_row(){
    long result{};
    int counts{};
    for(int row = buffer; row < matrix.size(); row++){
        for(int col =0; col< matrix.at(0).size(); col++){
            if(matrix.at(row).at(col) > 0) counts++;
        }  
        //remove row and add score 
        if(counts == matrix.at(0).size()){
            for(int col =0; col< matrix.at(0).size(); col++){
                matrix.at(row).at(col) = 0;}    
            result += poin;
        //shift
            for(int i = row; i>=buffer; i--){
                for(int j = 0; j< matrix.at(0).size(); j++){
                    matrix.at(i).at(j) = matrix.at(i-1).at(j);    
                }
            }
        }
        counts = 0;        
    }
    return result;
} 

bool engine::action(int &act, char &rotate){

    //set new cube
    set_cube();
    //remove steps
    if (temp.size() > 0){
        for(auto t:temp){
            for(int i = 0; i< 4; i++){
                matrix.at(t.at(i).at(0)).at(t.at(i).at(1))=0;
            }
        }       
        temp.erase(temp.begin());
    }

    //rotation
    rotation(rotate);
    //move adj
    if((check_left() && act == -1) || (check_right() && act == 1))
        act = 0;

    m_col1 += act;
    m_col2 += act;
    m_col3 += act;
    m_col4 += act;
    matrix.at(m_row1).at(m_col1) = color_n;
    matrix.at(m_row2).at(m_col2) = color_n;
    matrix.at(m_row3).at(m_col3) = color_n;
    matrix.at(m_row4).at(m_col4) = color_n;

    temp.push_back(std::vector<std::vector<int>>{{m_row1,m_col1},{m_row2,m_col2},{m_row3,m_col3}
              ,{m_row4,m_col4}});
    
    //hit 
    if(check_hit()){
        if(check_game())return false;
        score += check_row();
        if(score> old_score*10/100){level_n +=1; old_score=score;}
        temp.clear();
        color_n = rand() % 6 + 1;
        cube_shape = second_cube;
        rotate_ind = 0;
        m_row1 = 0;m_col1 = 0;m_row2 = 0;m_col2 = 0;m_row3 = 0;m_col3 = 0;m_row4 = 0;m_col4 = 0;
    }
    else{
    //droping
        m_row1++;
        m_row2++;
        m_row3++;
        m_row4++;
    }

    //reset the value    
    act = 0;
    rotate = ' ';
    return true;
}

void engine::set_cube(){
    if(m_row1+m_row2+m_row3+m_row4+m_col1+m_col2+m_col3+m_col4 ==0){
        second_cube = rand() % 7;
        switch(cube_shape){
            case 0:m_row1 = 0;m_col1 = 4;m_row2 = 1;m_col2 = 4;m_row3 = 2;m_col3 = 4;m_row4 = 1;m_col4 = 5;
                break;//T
            case 1:m_row1 = 0;m_col1 = 4;m_row2 = 1;m_col2 = 4;m_row3 = 2;m_col3 = 4;m_row4 = 2;m_col4 = 5;
                break;//L
            case 2:m_row1 = 0;m_col1 = 5;m_row2 = 1;m_col2 = 5;m_row3 = 2;m_col3 = 5;m_row4 = 2;m_col4 = 4;
                break;//rL
            case 3:m_row1 = 0;m_col1 = 5;m_row2 = 1;m_col2 = 5;m_row3 = 1;m_col3 = 4;m_row4 = 2;m_col4 = 4;
                break;//Z
            case 4:m_row1 = 0;m_col1 = 4;m_row2 = 1;m_col2 = 4;m_row3 = 1;m_col3 = 5;m_row4 = 2;m_col4 = 5;
                break;//rZ
            case 5:m_row1 = 0;m_col1 = 4;m_row2 = 0;m_col2 = 5;m_row3 = 1;m_col3 = 4;m_row4 = 1;m_col4 = 5;
                break;//O
            case 6:m_row1 = 0;m_col1 = 4;m_row2 = 1;m_col2 = 4;m_row3 = 2;m_col3 = 4;m_row4 = 3;m_col4 = 4;
                break;//I
            default: break;
        }
    }    
}

std::vector <std::vector<short>> engine::get_m(){
    return matrix;
}        
long engine::get_level(){
    return level_n;       
}
long engine::get_score(){
    return score;       
}
char engine::get_second(){
    char ans{7};
    switch(second_cube){
        case 0:ans = 'T';break;//T
        case 1:ans = 'L';break;//L
        case 2:ans = 'l';break;//rL
        case 3:ans = 'Z';break;//Z
        case 4:ans = 'z';break;//rZ
        case 5:ans = 'O';break;//O
        case 6:ans = 'I';break;//I
        default: break;
    }        
    return ans;
}

bool engine::check_hit(){
    std::vector<std::pair<int,int>> check_temp,ch_temp;
    bool check{false};

    ch_temp.push_back(std::make_pair(m_row1, m_col1));
    ch_temp.push_back(std::make_pair(m_row2, m_col2));
    ch_temp.push_back(std::make_pair(m_row3, m_col3));
    ch_temp.push_back(std::make_pair(m_row4, m_col4));
    check_temp = ch_temp;

    //find bottom cell
    for(int i = 0; i<4; i++){
    check_temp.erase(std::remove_if(check_temp.begin(),check_temp.end(), [&](auto &t){return t == std::make_pair(ch_temp.at(i).first-1, ch_temp.at(i).second);}),check_temp.end());
    }
    for(auto ch:check_temp){
        if(ch.first+1 < matrix.size())
            if(matrix.at(ch.first+1).at(ch.second)!=0)check = true; 
    }
    ch_temp.clear();

    //bottom
    if(m_row1 == matrix.size()-1 || m_row2 == matrix.size()-1 || m_row3 == matrix.size()-1 || m_row4 == matrix.size()-1)
        return true;
    //hit cube
    else if(check)
        return true;
    else
        return false;
}

bool engine::check_right(){
    std::vector<std::pair<int,int>> check_temp,ch_temp;
    bool check{false};

    ch_temp.push_back(std::make_pair(m_row1, m_col1));
    ch_temp.push_back(std::make_pair(m_row2, m_col2));
    ch_temp.push_back(std::make_pair(m_row3, m_col3));
    ch_temp.push_back(std::make_pair(m_row4, m_col4));
    check_temp = ch_temp;

    //find right cell
    for(int i = 0; i<4; i++){
    check_temp.erase(std::remove_if(check_temp.begin(),check_temp.end(), [&](auto &t){return t == std::make_pair(ch_temp.at(i).first, ch_temp.at(i).second-1);}),check_temp.end());
    }
    for(auto ch:check_temp){
        if(ch.second < matrix.at(0).size())
            if(ch.second == matrix.at(0).size()-1 || matrix.at(ch.first).at(ch.second+1)!=0)check = true; 
    }
    ch_temp.clear();

    return check;
}

bool engine::check_left(){
    std::vector<std::pair<int,int>> check_temp,ch_temp;
    bool check{false};

    ch_temp.push_back(std::make_pair(m_row1, m_col1));
    ch_temp.push_back(std::make_pair(m_row2, m_col2));
    ch_temp.push_back(std::make_pair(m_row3, m_col3));
    ch_temp.push_back(std::make_pair(m_row4, m_col4));
    check_temp = ch_temp;

    //find left cell
    for(int i = 0; i<4; i++){
    check_temp.erase(std::remove_if(check_temp.begin(),check_temp.end(), [&](auto &t){return t == std::make_pair(ch_temp.at(i).first, ch_temp.at(i).second+1);}),check_temp.end());
    }
    for(auto ch:check_temp){
        if(ch.second >= 0)
            if(ch.second == 0 || matrix.at(ch.first).at(ch.second - 1)!=0)check = true; 
    }
    ch_temp.clear();

    return check;
}


