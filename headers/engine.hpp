#ifndef GAME_TETRIS
#define GAME_TETRIS

#include <vector>
#include <stdlib.h>

class engine{
private:
    long score{}, old_score{}, level_n{}, poin{2};
    static int color_n, cube_shape, second_cube, m_row1, m_col1, m_row2, m_col2, m_row3, m_col3, m_row4, m_col4, rotate_ind;
    const int buffer{8};
    std::vector <std::vector<short>> matrix;
    std::vector<std::vector<std::vector<int>>>temp{};
public:
    engine(unsigned x, unsigned y):matrix{y+buffer, std::vector<short>(x,0)}{};
    ~engine()=default;

    void set_cube();
    void rotation(char r);
    bool action(int &act, char &rotate);
    bool check_hit();
    bool check_left();
    bool check_right();
    bool check_game();
    void check_rotation(int y1,int x1, int y2,int x2, int y3,int x3,int y4,int x4);
    long check_row();
    long get_level();
    long get_score();
    char get_second();
    std::vector <std::vector<short>> get_m();
};


#endif
