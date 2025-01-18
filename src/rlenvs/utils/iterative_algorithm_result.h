#ifndef ITERATIVE_ALGORITHM_RESULT_H
#define ITERATIVE_ALGORITHM_RESULT_H

#include "rlenvs/rlenvs_types_v2.h"
#include <ostream>
#include <chrono>
#include <vector>

namespace rlenvscpp{
namespace utils{

///
/// \brief The IterativeAlgorithmResult struct. Helper
/// struct to assemble the result of an iterative algorithm
///
struct IterativeAlgorithmResult  {

    ///
    /// \brief tolerance
    ///
    real_t tolerance;

    ///
    /// \brief residual
    ///
    real_t residual;

    ///
    /// \brief num_iterations
    ///
    uint_t num_iterations;

    ///
    /// \brief converged
    ///
    bool converged=false;

    ///
    /// \brief total_time
    ///
    std::chrono::duration<real_t> total_time;

    ///
    /// \brief residuals
    ///
    std::vector<real_t> residuals;

    ///
    /// \brief IterativeAlgorithmResult
    ///
    IterativeAlgorithmResult() = default;

    ///
    /// \brief IterativeAlgorithmResult
    ///
    IterativeAlgorithmResult(real_t tol, real_t res,
                             uint_t nitrs, 
							 std::chrono::duration<real_t> time);

    ///
    /// \brief print
    ///
    std::ostream& print(std::ostream& out)const;
};


inline
std::ostream& operator<<(std::ostream& out, 
                         const IterativeAlgorithmResult& result){
    return result.print(out);
}

}
}
#endif // ITERATIVE_ALGORITHM_RESULT_H
