#include <iostream>
#include <string>
#include <vector>

using uint = unsigned int;

std::string join(std::vector<uint> vec) {
    std::string out = "";
    for (uint n : vec) out.push_back(n + 'a');
    return out;
}

int main() {
    std::cout << "Number of people: ";
    uint number_of_people;
    std::cin >> number_of_people;
    uint skip_value;
    std::cout << "Skip value: ";
    std::cin >> skip_value;

    std::vector<uint> people;

    for (uint i = 0; i < number_of_people; i++) people.push_back(i);

    uint killer_i = 0;

    while (people.size() > skip_value) {
        uint dead_i = (killer_i + skip_value) % people.size();
        std::cout << join(people) << ": " << (char)(people[killer_i] + 'a')
                  << " killed " << (char)(people[dead_i] + 'a') << ".\n";

        people.erase(people.begin() + dead_i);
        killer_i = dead_i % people.size();
    }

    std::cout << "Survivors: " << join(people) << "\n";

    #ifdef _WIN32
    system("pause");
    #endif

    return 0;
}
