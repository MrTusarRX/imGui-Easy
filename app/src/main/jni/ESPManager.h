
void *myPlayer = NULL;
struct enemy_t {
    void *object;
    Vector3 location;
    int health;

};
class ESPManager {
public:
    std::vector<enemy_t *> *enemies;

    ESPManager() {
        enemies = new std::vector<enemy_t *>();
    }
    bool isEnemyPresent(void *enemyObject) {
        for (std::vector<enemy_t *>::iterator it = enemies->begin(); it != enemies->end(); it++) {
            if ((*it)->object == enemyObject) {
                return true;
            }
        }
        return false;
    }
    void removeEnemy(enemy_t *enemy) {
        for (int i = 0; i < enemies->size(); i++) {
            if ((*enemies)[i] == enemy) {
                enemies->erase(enemies->begin() + i);
                return;
            }
        }
    }
    void tryAddEnemy(void *enemyObject) {
        if (isEnemyPresent(enemyObject)) {
            return;
        }

        if (IsPlayerDead(enemyObject)) {
            return;
        }

        enemy_t *newEnemy = new enemy_t();

        newEnemy->object = enemyObject;

        enemies->push_back(newEnemy);
    }
    void updateEnemies(void *enemyObject) {
        for (int i = 0; i < enemies->size(); i++) {
            enemy_t *current = (*enemies)[i];

            if (IsPlayerDead(current->object)) {
                enemies->erase(enemies->begin() + i);
            }
        }
    }
    void removeEnemyGivenObject(void *enemyObject) {
        for (int i = 0; i < enemies->size(); i++) {
            if ((*enemies)[i]->object == enemyObject) {
                enemies->erase(enemies->begin() + i);
                return;
            }
        }
    }

};



