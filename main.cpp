#include <iostream>
#include <fstream>
#include <map>
#include <chrono>


using namespace std;

class ProcessIngredients {
private:
    map <string, map <string, double >> recipeDetails;

public:
    void ProcessIngredientAmounts(const string &file) {
        ifstream ingredientsFile(file);
        string ingredientRecipe, ingredient;
        double ingredientQuantity;

        //Fills in the recipeDetails map with the recipe name, ingredient and the
        //order amount
        while (ingredientsFile >> ingredientRecipe >> ingredient >> ingredientQuantity) {
                recipeDetails[ingredientRecipe][ingredient] += ingredientQuantity;
            }
        ingredientsFile.close();
    }

    void calculateIngredientTotal(const string &file) {
        ifstream ordersFile(file);
        map <string, double> totalIngredients;
        string orderRecipe;
        double orderQuantity;

        //Fills in the totalIngredients map with the ingredient and the correct total
        //ingredient amount needed for all the recipes using the previous map and the order file
        while (ordersFile >> orderRecipe >> orderQuantity) {
                for (const auto &processOrders : recipeDetails[orderRecipe]) {
                    totalIngredients[processOrders.first] += processOrders.second * orderQuantity;
                }
            }
        ordersFile.close();
        //outputs the ingredient and the total ingredient amount needed
        // from the totalIngredients map
        for (const auto &ingredientAmount : totalIngredients) {
            cout << ingredientAmount.first << " " << ingredientAmount.second << endl;
        }
    }
};

int main() {
    auto startTime = chrono::high_resolution_clock::now();

    ProcessIngredients ingredientProcessor;
    ingredientProcessor.ProcessIngredientAmounts("ingredients.txt");
    ingredientProcessor.calculateIngredientTotal("orders.txt");

    auto endTime = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(endTime - startTime).count();
    cout << "Elapsed time: " << duration << " ns" << endl;

    return 0;
}
