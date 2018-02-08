#include <iostream>
#include <vevtor>
#include "Result.hpp"

class CameraModule{
private:
    std::vector<Result> results;
    
};

inline std::vector<Result> getResults(){
    return results;
}

inline void setResults(std::vector<Result> results){
    this.results = results;
}
