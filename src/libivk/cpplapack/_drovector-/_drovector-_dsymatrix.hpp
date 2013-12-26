//=============================================================================
/*! _drovector*_dsymatrix operator */
inline _drovector operator*(const _drovector& vec, const _dsymatrix& mat)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _drovector&, const _dsymatrix&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(vec.L!=mat.N){
    std::cerr << "[ERROR] operator*(const drovector&, const _dsymatrix&)"
              << std::endl
              << "These vector and matrix can not make a product."
              << std::endl
              << "Your input was (" << vec.L << ") * ("
              << mat.N << "x" << mat.N << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  drovector newvec(mat.N);
  dsymv_( 'L', mat.N, 1.0, mat.Array, mat.N,
          vec.Array, 1, 0.0, newvec.array, 1 );
  
  vec.destroy();
  mat.destroy();
  return _(newvec);
}
