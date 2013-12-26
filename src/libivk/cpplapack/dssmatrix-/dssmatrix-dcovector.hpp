//=============================================================================
/*! dssmatrix*dcovector operator */
inline _dcovector operator*(const dssmatrix& mat, const dcovector& vec)
{
#ifdef  CPPL_VERBOSE
  std::cerr << "# [MARK] operator*(const dssmatrix&, const dcovector&)"
            << std::endl;
#endif//CPPL_VERBOSE
  
#ifdef  CPPL_DEBUG
  if(mat.N!=vec.L){
    std::cerr << "[ERROR] operator*(const dssmatrix&, const dcovector&)"
              << std::endl
              << "These matrix and vector can not make a product." << std::endl
              << "Your input was (" << mat.M << "x" << mat.N << ") * ("
              << vec.L << ")." << std::endl;
    exit(1);
  }
#endif//CPPL_DEBUG
  
  dcovector newvec(mat.M);
  newvec.zero();
  
  for(int c=0; c<mat.VOL; c++){
    newvec(mat.Indx[c]) +=mat.Array[c]*vec(mat.Jndx[c]);
  }
  
  return _(newvec);
}
