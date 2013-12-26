//=============================================================================
/*! _dsymatrix*_dcovector operator */
inline _dcovector operator*(const _dsymatrix& mat, const _dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _dsymatrix&, const _dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.N!=vec.L){
    std::cerr << "[ERROR] operator*(const _dsymatrix&, const _dcovector&)"
              << std::endl
              << "These matrix and vector can not make a product." << std::endl
              << "Your input was (" << mat.N << "x" << mat.N << ") * ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dcovector newvec(mat.N);
  dsymv_( 'L', mat.N, 1.0, mat.Array, mat.N,
          vec.Array, 1, 0.0, newvec.array, 1 );
  
  mat.destroy();
  vec.destroy();
  return _(newvec);
}
