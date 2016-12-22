//
// Created by julie on 20/12/2016.
//

#ifndef GAMEOFLIFE_CANONICALTREENODE_H
#define GAMEOFLIFE_CANONICALTREENODE_H

#include "TreeNode.h"
#include "TreeHashMap.h"
namespace std {
    template<>
    struct hash<TreeNode*> {
        typedef TreeNode* argument_type;
        typedef std::size_t result_type;

        result_type operator()(argument_type const &s) const {
            if (s->getLevel() == 0) {
                return (unsigned int) s->getPopulation();
            }
            std::size_t hashNw = 0;
            if (s->getNw() != nullptr)
                hashNw = std::hash<TreeNode*>{}(s->getNw());
            result_type const h1(hashNw);

            std::size_t hashNe = 0;
            if (s->getNe() != nullptr)
                hashNe = std::hash<TreeNode*>{}(s->getNe());
            result_type const h2(hashNe);

            std::size_t hashSw = 0;
            if (s->getSw() != nullptr)
                hashSw = std::hash<TreeNode*>{}(s->getSw());
            result_type const h3(hashSw);

            std::size_t hashSe = 0;
            if (s->getSe() != nullptr)
                hashSe = std::hash<TreeNode*>{}(s->getSe());
            result_type const h4(hashSe);
            unsigned int seed = 0;
            seed ^= h1 + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= h2 + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= h3 + 0x9e3779b9 + (seed<<6) + (seed>>2);
            seed ^= h4 + 0x9e3779b9 + (seed<<6) + (seed>>2);
            return seed;
        }
    };
}

class CanonicalTreeNode : public TreeNode{
public:
    CanonicalTreeNode(bool living);
    CanonicalTreeNode(TreeNode *nw,TreeNode* ne,TreeNode* sw, TreeNode* se);
    CanonicalTreeNode(int level);

    TreeNode* intern();

    static TreeNode * create();
    virtual TreeNode * create(bool living) override;
    virtual TreeNode * create(TreeNode *nw,TreeNode* ne,TreeNode* sw, TreeNode* se) override;
    virtual TreeNode * create(int level) override;





};


#endif //GAMEOFLIFE_CANONICALTREENODE_H
