//
// Created by oem on 6/13/21.
//

#ifndef BOMBERMAN_CUBE_HPP
#define BOMBERMAN_CUBE_HPP

#include <raylib.h>
#include "IGameObject.hpp"

class Cube : public IGameObject {
    public:

    typedef struct memory_chunk_cube_s {
        char name[80];
        float cube_size;
        float translation_x;
        float translation_y;
        float translation_z;
        bool destructable;
        Color color_face;
        Color color_edge;
    } memory_chunk_cube;

    Cube(float x, float z, Color color_face, Color color_edge, float width,
        bool destructable
    );
    Cube(Vector3 position, Vector3 size, Texture texture, bool destructable);

    Cube(void *);

    ~Cube();
    virtual void draw() override;
    virtual void update(std::list<IGameObject *> *objects) override;
    unsigned long get_storage_size() override {return sizeof(memory_chunk_cube);}
    void *get_memory_to_store() override;

    protected:
    bool isSquareCube = true;

    Vector3 cubePosition;
    Color color_face;
    Color color_edge;
    float cube_size;

    Model cubeModel;
};

#endif //BOMBERMAN_CUBE_HPP
