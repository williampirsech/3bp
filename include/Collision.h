#pragma once

#include "SFML/graphics.hpp"
#include "Util.h"
#include "Movable.h"

class Collision {
    public:
    static bool collidesWith(const Movable& m1, const Movable& m2) {
        for (int k=0; k<m2.vert.getVertexCount()-1; ++k) {
            // ort is a "perpendicular line"
            sf::Vector2f ort = {
                m2.vert[k+1].position.y-m2.vert[k].position.y,
                m2.vert[k].position.x-m2.vert[k+1].position.x
            };
            auto proj1 = dot(m1.vert[0].position, ort); // projected component onto the ort. line
            auto proj2 = dot(m2.vert[0].position, ort);
            short comp = proj1 < proj2 ? +1 : -1;
            int j=1;
            for (; j < m1.vert.getVertexCount() && proj1 <= proj2; ++j)
                proj1 = max(proj1, dot(m1.vert[j].position,ort));
            if (j == m1.vert.getVertexCount()) {
                j = 1;
                for (; j < m2.vert.getVertexCount() && proj1 <= proj2; ++j)
                    proj2 = min(proj2, dot(m2.vert[j].position,ort));
                if (j == m2.vert.getVertexCount()) return false;
            }

        }
        return true;
    }
};