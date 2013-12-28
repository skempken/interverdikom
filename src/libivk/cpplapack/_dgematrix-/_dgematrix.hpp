//=============================================================================
//! (DO NOT USE) Smart-temporary Real Double-precision General Dence Matrix Class
class _dgematrix
{
public:
  //// objects ////
  mutable long M; //!< matrix row size
  mutable long N; //!< matrix column size
  mutable double* Array; //!< 1D array to store matrix data
  mutable double** Darray; //!< array of pointers of column head addresses

  //// constructor ////
  inline _dgematrix();
  inline _dgematrix(const _dgematrix&);
  inline ~_dgematrix(); //destructor
  
  //// cast ////
  inline operator _zgematrix();
  
  //// io ////
  inline double& operator()(const long&, const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const dgematrix&);
  inline void write(const char *) const;
  
  //// misc ////
  inline void destroy() const;
  
  //// calc ////
  inline friend _dgematrix t(const _dgematrix&);
  inline friend _dgematrix i(const _dgematrix&);
  inline friend void idamax(long&, long&, const _dgematrix&);
  inline friend double damax(const _dgematrix&);
  
  //// unary ////
  inline friend const _dgematrix& operator+(const _dgematrix&);
  inline friend _dgematrix operator-(const _dgematrix&);
  
  //// + ////
  inline friend _dgematrix operator+(const  dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const _dgematrix&);
  
  inline friend _dgematrix operator+(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dgbmatrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const _dgbmatrix&);
  
  inline friend _dgematrix operator+(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const _dgematrix&);
  
  //// - ////
  inline friend _dgematrix operator-(const  dgematrix&);
  
  inline friend _dgematrix operator-(const  dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const _dgematrix&);
  
  inline friend _dgematrix operator-(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dgbmatrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const  dgbmatrix&);  
  inline friend _dgematrix operator-(const _dgematrix&, const _dgbmatrix&);
  
  inline friend _dgematrix operator-(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const _dgematrix&);
  
  //// * ////
  inline friend _dgematrix operator*(const  dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dgematrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const _dgematrix&);
  
  inline friend _dgematrix operator*(const  dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dgbmatrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const _dgbmatrix&);
  
  inline friend _dgematrix operator*(const  dgematrix&, const     double&);
  inline friend _dgematrix operator*(const _dgematrix&, const     double&);
  inline friend _dgematrix operator*(const     double&, const _dgematrix&);
  inline friend _dgematrix operator*(const     double&, const  dgematrix&);
  
  inline friend _dgematrix operator*(const  dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const  dgbmatrix&, const _dgematrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const _dgematrix&);
  
  inline friend _dgematrix operator*(const  dcovector&, const  drovector&);
  inline friend _dgematrix operator*(const  dcovector&, const _drovector&);
  inline friend _dgematrix operator*(const _dcovector&, const  drovector&);
  inline friend _dgematrix operator*(const _dcovector&, const _drovector&);
  
  inline friend _drovector operator*(const  drovector&, const _dgematrix&);
  inline friend _drovector operator*(const _drovector&, const _dgematrix&);
  inline friend _dcovector operator*(const _dgematrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dgematrix&, const _dcovector&);
  
  //// / ////
  inline friend _dgematrix operator/(const  dgematrix&, const     double&);
  inline friend _dgematrix operator/(const _dgematrix&, const     double&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class  drovector;
  friend class _drovector;
};
