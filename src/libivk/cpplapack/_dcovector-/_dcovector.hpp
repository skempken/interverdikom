//=============================================================================
//! (DO NOT USE) Smart-temporary Real Double-precision Column Vector Class
class _dcovector
{
public:
  //// objects ////
  mutable long L; //!< vector size
  mutable double* Array; //!< 1D Array to store vector data
  
  //// constructor ////
  inline _dcovector();
  inline _dcovector(const _dcovector&);
  inline ~_dcovector(); //destructor
  
  //// cast ////
  inline operator _zcovector();
  
  //// io ////
  inline double& operator()(const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const _dcovector&);
  inline void write(const char *) const;
  
  //// calc ////
  inline friend _drovector t(const dcovector&);
  inline friend double nrm2(const dcovector&);
  inline friend long idamax(const dcovector&);
  inline friend double damax(const dcovector&);
  
  //// misc ////
  inline void destroy() const;
  
  //// unary ////
  inline friend const _dcovector& operator+(const _dcovector&);
  inline friend _dcovector operator-(const _dcovector&);

  //// + ////
  inline friend _dcovector operator+(const  dcovector&, const  dcovector&);
  inline friend _dcovector operator+(const  dcovector&, const _dcovector&);
  inline friend _dcovector operator+(const _dcovector&, const  dcovector&);
  inline friend _dcovector operator+(const _dcovector&, const _dcovector&);
  
  //// - ////
  inline friend _dcovector operator-(const  dcovector&, const  dcovector&);
  inline friend _dcovector operator-(const  dcovector&, const _dcovector&);
  inline friend _dcovector operator-(const _dcovector&, const  dcovector&);
  inline friend _dcovector operator-(const _dcovector&, const _dcovector&);

  //// * ////
  inline friend _dcovector operator*(const  dgematrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dgematrix&, const _dcovector&);
  inline friend _dcovector operator*(const _dgematrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dgematrix&, const _dcovector&);
  
  inline friend _dcovector operator*(const  dgbmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dgbmatrix&, const _dcovector&);
  inline friend _dcovector operator*(const _dgbmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dgbmatrix&, const _dcovector&);
  
  inline friend _dcovector operator*(const  dcovector&, const     double&);
  inline friend _dcovector operator*(const _dcovector&, const     double&);
  inline friend _dcovector operator*(const     double&, const  dcovector&);
  inline friend _dcovector operator*(const     double&, const _dcovector&);
  
  inline friend _dgematrix operator*(const _dcovector&, const  drovector&);
  inline friend _dgematrix operator*(const _dcovector&, const _drovector&);
  inline friend     double operator*(const  drovector&, const _dcovector&);
  inline friend     double operator*(const _drovector&, const _dcovector&);
  
  //// / ////
  inline friend _dcovector operator/(const  dcovector&, const     double&);
  inline friend _dcovector operator/(const _dcovector&, const     double&);
  
  //// % ////
  inline friend     double operator%(const  dcovector&, const _dcovector&);
  inline friend     double operator%(const _dcovector&, const  dcovector&);
  inline friend     double operator%(const _dcovector&, const _dcovector&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class  dcovector;
  friend class  drovector;
  friend class _drovector;
};
