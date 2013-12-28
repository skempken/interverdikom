//=============================================================================
//! (DO NOT USE) Smart-temporary Real Double-precision Sparse Matrix Class
class _dssmatrix
{
public:
  //// objects ////
  mutable long M; //!< matrix row size
  mutable long N; //!< matrix column size
  mutable long CAP; //!< the length of data arrays
  mutable long VOL; //!< the number of non-zero components
  mutable double* Array; //!< 1D array to store non-zero matrix data
  mutable long* Indx; //!< 1D array to store the i-index of non-zero matrix components
  mutable long* Jndx; //!< 1D array to store the j-index of non-zero matrix components
  
  //// constructor ////
  inline _dssmatrix();
  inline _dssmatrix(const _dssmatrix&);
  inline ~_dssmatrix(); //destructor
  
  //// cast ////
  inline operator _zssmatrix();
  
  //// io ////
  inline double operator()(const long&, const long&) const;
  inline friend std::ostream& operator<<(std::ostream&, const _dssmatrix&);
  inline void write(const char *) const;

  //// misc ////
  inline void destroy() const;
  
  //// calc ////
  inline friend _dssmatrix t(const dssmatrix&);
  inline friend void idamax(long&, long&, const dssmatrix&);
  inline friend double damax(const dssmatrix&);
  
  //// unary ////
  inline friend const _dssmatrix& operator+(const _dssmatrix&);
  inline friend _dssmatrix operator-(const _dssmatrix&);
  
  //// + ////
  inline friend _dssmatrix operator+(const  dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator+(const  dssmatrix&, const _dssmatrix&);
  inline friend _dssmatrix operator+(const _dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator+(const _dssmatrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator+(const _dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator+(const _dssmatrix&, const _dgematrix&);
  inline friend _dgematrix operator+(const _dgematrix&, const _dssmatrix&);
  inline friend _dgematrix operator+(const  dgematrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator+(const _dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator+(const _dssmatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator+(const _dgbmatrix&, const _dssmatrix&);
  inline friend _dgematrix operator+(const  dgbmatrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator+(const _dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator+(const _dssmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator+(const _dsymatrix&, const _dssmatrix&);
  inline friend _dgematrix operator+(const  dsymatrix&, const _dssmatrix&);
  
  //// - ////
  inline friend _dssmatrix operator-(const  dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator-(const  dssmatrix&, const _dssmatrix&);
  inline friend _dssmatrix operator-(const _dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator-(const _dssmatrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator-(const _dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator-(const _dssmatrix&, const _dgematrix&);
  inline friend _dgematrix operator-(const _dgematrix&, const _dssmatrix&);
  inline friend _dgematrix operator-(const  dgematrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator-(const _dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator-(const _dssmatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator-(const _dgbmatrix&, const _dssmatrix&);
  inline friend _dgematrix operator-(const  dgbmatrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator-(const _dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator-(const _dssmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator-(const _dsymatrix&, const _dssmatrix&);
  inline friend _dgematrix operator-(const  dsymatrix&, const _dssmatrix&);
  
  //// * ////
  inline friend _dssmatrix operator*(const  dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator*(const  dssmatrix&, const _dssmatrix&);
  inline friend _dssmatrix operator*(const _dssmatrix&, const  dssmatrix&);
  inline friend _dssmatrix operator*(const _dssmatrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator*(const _dssmatrix&, const  dgematrix&);
  inline friend _dgematrix operator*(const _dssmatrix&, const _dgematrix&);
  inline friend _dgematrix operator*(const _dgematrix&, const _dssmatrix&);
  inline friend _dgematrix operator*(const  dgematrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator*(const _dssmatrix&, const  dgbmatrix&);
  inline friend _dgematrix operator*(const _dssmatrix&, const _dgbmatrix&);
  inline friend _dgematrix operator*(const _dgbmatrix&, const _dssmatrix&);
  inline friend _dgematrix operator*(const  dgbmatrix&, const _dssmatrix&);
  
  inline friend _dgematrix operator*(const _dssmatrix&, const  dsymatrix&);
  inline friend _dgematrix operator*(const _dssmatrix&, const _dsymatrix&);
  inline friend _dgematrix operator*(const _dsymatrix&, const _dssmatrix&);
  inline friend _dgematrix operator*(const  dsymatrix&, const _dssmatrix&);
  
  inline friend _dcovector operator*(const  dssmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dssmatrix&, const _dcovector&);
  
  inline friend _drovector operator*(const  drovector&, const _dssmatrix&);
  inline friend _drovector operator*(const _drovector&, const _dssmatrix&);
  
  inline friend _dssmatrix operator*(const  dssmatrix&, const     double&);
  inline friend _dssmatrix operator*(const _dssmatrix&, const     double&);
  inline friend _dssmatrix operator*(const     double&, const  dssmatrix&);
  inline friend _dssmatrix operator*(const     double&, const _dssmatrix&);
  
  //// / ////
  inline friend _dssmatrix operator/(const  dssmatrix&, const     double&);
  inline friend _dssmatrix operator/(const _dssmatrix&, const     double&);
  
  //// friend classes ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class  dsymatrix;
  friend class _dsymatrix;
  friend class  dssmatrix;
  friend class  dcovector;
  friend class _dcovector;
  friend class  drovector;
  friend class _drovector;
};
