//=============================================================================
/*! _zssmatrix*zcovector operator */
inline _zcovector operator*(const _zssmatrix& mat, const zcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const _zssmatrix&, const zcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.N!=vec.L){
    std::cerr << "[ERROR] operator*(const _zssmatrix&, const zcovector&)"
              << std::endl
              << "These matrix and vector can not make a product." << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ") * ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  zcovector newvec(mat.M);
  newvec.zero();
  
  for(int c=0; c<mat.VOL; c++){
    newvec(mat.Indx[c]) +=mat.Array[c]*vec(mat.Jndx[c]);
  }
  
  mat.destroy();
  return _(newvec);
}
