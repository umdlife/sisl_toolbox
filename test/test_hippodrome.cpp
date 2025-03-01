#include "test/test_path.hpp"
#include <vector>

#include <iomanip>
using namespace sisl_toolbox;
int main() {

    /***************** Path creation *****************/

    auto start = std::chrono::high_resolution_clock::now();
    // unsync the I/O of C and C++.
    std::ios_base::sync_with_stdio(false);

    std::shared_ptr<Path> hippodrome;

    // auto test = std::make_shared<StraightLine>(Eigen::Vector3d{50, 10, 0}, Eigen::Vector3d{50, -10, 20});
    // std::cout << "*************************  TEST  *************************" << std::endl;
    // std::cout << *test << std::endl;
    // std::cout << "StartPoint: [" << test->StartPoint()[0] << ", " << test->StartPoint()[1] << ", " << test->StartPoint()[2] 
    //     << "], endPoint: [" << test->EndPoint()[0] << ", " << test->EndPoint()[1] << ", " << test->EndPoint()[2] 
    //     << "]" << std::endl;

    try {
        hippodrome = PathFactory::NewHippodrome(std::vector<Eigen::Vector3d>{Eigen::Vector3d{-50, 5, 0}, Eigen::Vector3d{-50, -5, 1},
                                                                            Eigen::Vector3d{-45, -5, 1}, Eigen::Vector3d{-45, 5, 2}});

        // hippodrome = PathFactory::NewHippodrome(std::vector<Eigen::Vector3d>{Eigen::Vector3d{10, -50, 0}, Eigen::Vector3d{10, 50, 0}, 
        //                                                                    Eigen::Vector3d{-10, 50, 0}, Eigen::Vector3d{-10, -50, 0}});

        std::cout << *hippodrome << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        // Calculating total time taken by the program.
        double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        time_taken *= 1e-9;  
        std::cout << "Time taken to build the Path object : " << std::fixed << std::setprecision(9) << time_taken  << " sec" << std::endl;
        std::cout << std::fixed << std::setprecision(3); 

        PersistenceManager::SaveObj(hippodrome->Sampling(200), "/home/antonio/sisl_toolbox/script/path.txt");

        double abscissaCurve_m{0};
        int curveId{0};

        // std::cout << std::endl << hippodrome->Name() << " is composed by: " << std::endl;
        // for(int i = 0; i < hippodrome->CurvesNumber(); ++i) {
        //     std::cout << i << ". " << *hippodrome->Curves()[i] << "\n" 
        //         << "StartPoint: [" << (hippodrome->Curves()[i])->StartPoint()[0] << ", " << (hippodrome->Curves()[i])->StartPoint()[1] 
        //         << ", " << (hippodrome->Curves()[i])->StartPoint()[2] << "], endPoint: [" << (hippodrome->Curves()[i])->EndPoint()[0] 
        //         << ", " << (hippodrome->Curves()[i])->EndPoint()[1] << ", " << (hippodrome->Curves()[i])->EndPoint()[2] 
        //         << "]" << std::endl;
        // }
        
        // Eigen::Vector3d tangent;
        // Eigen::Vector3d normal;
        // Eigen::Vector3d binormal;

        // hippodrome->EvalTangentFrame(50, tangent, normal, binormal);
        // std::cout << "At 50 -> tangent [" << tangent[0] << ", " << tangent[1] << ", " << tangent[2] << "], normal: [" << normal[0] 
        //         << ", " << normal[1] << ", " << normal[2] << "], binormal [" << binormal[0] << ", " << binormal[1] << ", " << binormal[2] 
        //         << "]" << std::endl;
        
        // hippodrome->EvalTangentFrame(115, tangent, normal, binormal);
        // std::cout << "At 115 -> tangent [" << tangent[0] << ", " << tangent[1] << ", " << tangent[2] << "], normal: [" << normal[0] 
        //         << ", " << normal[1] << ", " << normal[2] << "], binormal [" << binormal[0] << ", " << binormal[1] << ", " << binormal[2] 
        //         << "]" << std::endl;
        
        // hippodrome->EvalTangentFrame(181, tangent, normal, binormal);
        // std::cout << "At 181 -> tangent [" << tangent[0] << ", " << tangent[1] << ", " << tangent[2] << "], normal: [" << normal[0] 
        //         << ", " << normal[1] << ", " << normal[2] << "], binormal [" << binormal[0] << ", " << binormal[1] << ", " << binormal[2] 
        //         << "]" << std::endl;

        // hippodrome->EvalTangentFrame(245, tangent, normal, binormal);
        // std::cout << "At 245 -> tangent [" << tangent[0] << ", " << tangent[1] << ", " << tangent[2] << "], normal: [" << normal[0] 
        //         << ", " << normal[1] << ", " << normal[2] << "], binormal [" << binormal[0] << ", " << binormal[1] << ", " << binormal[2] 
        //         << "]" << std::endl;


        // auto test = std::make_shared<StraightLine>(Eigen::Vector3d{50, 10, 0}, Eigen::Vector3d{50, -10, 20});
        // std::cout << "*************************  TEST  *************************" << std::endl;
        // std::cout << *test << std::endl;
        // std::cout << "StartPoint: [" << test->StartPoint()[0] << ", " << test->StartPoint()[1] << ", " << test->StartPoint()[2] 
        //     << "], endPoint: [" << test->EndPoint()[0] << ", " << test->EndPoint()[1] << ", " << test->EndPoint()[2] 
        //     << "]" << std::endl;


        /***************** Parametrizations mapping *****************/
        
        double absPath_m{10};
        std::tie(abscissaCurve_m, curveId) = hippodrome->PathAbsToCurveAbs(absPath_m);
        std::cout << std::endl << "Given abscissa path " << absPath_m << ", convert in Curve parametrization -> curveId: " 
            << curveId << ", abscissaCurve_m: " << abscissaCurve_m << std::endl;
        absPath_m = hippodrome->CurveAbsToPathAbs(abscissaCurve_m, curveId);
        std::cout << "Inverse transformation -> Given curveId " << curveId << " and abscissaCurve_m: " << abscissaCurve_m 
            << " -> , abscissa path: " << absPath_m << std::endl;


        /***************** Intersection Problem  *****************/

        std::ofstream outputIntersection;
        outputIntersection.open ("/home/antonio/sisl_toolbox/script/intersectionPoints.txt");
        auto line = std::make_shared<StraightLine>(Eigen::Vector3d{7.5, -2, 0}, Eigen::Vector3d{7.5, 12, 0});
        auto linePath = std::make_shared<Path>();
        linePath->AddCurveBack(line);
        PersistenceManager::SaveObj(line->Sampling(200), "/home/antonio/sisl_toolbox/script/intersectingCurve.txt");

        auto intersectionPoints = hippodrome->Intersection(linePath);

        std::cout << std::endl << "Given -> " << *line << std::endl;
        std::cout << "The intersection points are:  "<< std::endl;

        double counter{1};
        for(auto const & point: intersectionPoints) {
            std::cout << "[" << point[0] << ", " << point[1] << ", " << point[2] << "]" << std::endl;
            outputIntersection << point[0] << " " << point[1] << " " << point[2] << " " << counter++ << "\n";
        }
        outputIntersection.close();


        /***************** Closest Point Problem  *****************/

        Eigen::Vector3d findNearThis{15.5, 13, 0};
        double abscissaClosest{0};
        int curveIdClosest{0};
        auto closestPoint = hippodrome->FindClosestPoint(findNearThis, curveIdClosest, abscissaClosest);

        std::cout << std::endl << "Starting from point [" << findNearThis[0] << ", " << findNearThis[1] << ", " << findNearThis[2] << "]"
            << " the closest point on the path is [" << closestPoint[0] << ", " << closestPoint[1] << ", " << closestPoint[2] << "]" << std::endl;
        
        std::ofstream outputFile;
        outputFile.open ("/home/antonio/sisl_toolbox/script/closestPoint.txt");
        outputFile << "FindNear " << findNearThis[0] << " " << findNearThis[1] << " " << findNearThis[2] << "\n";
        outputFile << "ClosestPoint " << closestPoint[0] << " " << closestPoint[1] << " " << closestPoint[2] << "\n";
        outputFile.close();


        /***************** Move Point Problem  *****************/

        double abscissaStartPoint{10};
        double offset{30};
        std::ofstream outputFile2;
        outputFile2.open ("/home/antonio/sisl_toolbox/script/movePoint.txt");

        auto startPoint = hippodrome->At(abscissaStartPoint);
        std::cout << std::endl << "Point at abscissa: " << abscissaStartPoint << " is [" << startPoint[0] << ", " 
            << startPoint[1] << ", " << startPoint[2] << "]" << std::endl;
        outputFile2 << abscissaStartPoint << " " << startPoint[0] << " " << startPoint[1] << " " << startPoint[2] << "\n";
        
        abscissaStartPoint += offset;
        startPoint = hippodrome->At(abscissaStartPoint);
        std::cout << "Moved at abscissa: " << abscissaStartPoint << " -> [" << startPoint[0] << ", " 
            << startPoint[1] << ", " << startPoint[2] << "]" << std::endl;
        outputFile2 << abscissaStartPoint << " " << startPoint[0] << " " << startPoint[1] << " " << startPoint[2] << "\n";

        outputFile2.close();


        /***************** Extract Path Section Problem  *****************/

        auto pathSection = hippodrome->ExtractSection(5, 10);
        PersistenceManager::SaveObj(pathSection->Sampling(100), "/home/antonio/sisl_toolbox/script/pathSection.txt");
    
    } catch(std::runtime_error const& exception) {
        std::cout << "Received exception from --> " << exception.what() << std::endl;
    }

    return 0;
}
