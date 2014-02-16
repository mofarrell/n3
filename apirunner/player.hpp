#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player {
    public:
        Player();

        /* Collision detection. */
        void collision(float p_x, float p_y, float p_z,
            float x_1, float x_2, float y_1, float y_2, float z_1, float z_2);
        void move(float x, float y, float z);
        void checkCollisions();
        void kill_player();
        void game_over();

        bool isDead;

        float x, y, z;

        int level;

};

#endif /* PLAYER_HPP */
