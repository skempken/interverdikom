//=============================================================================
//! Real Double-precision Column Vector Class
class dcovector
{
private:
  //// objects ////
  long L; //!< vector size (NOT accessible)
  double* Array; //!< 1D array to store vector data (NOT accessible)

public:
  //// const references ////
  long const& l; //!< vector size (readable)
  double* const& array; //!< 1D array to store vector data (readable)
  
  //// constructor ////
  inline dcovector();
  inline dcovector(const dcovector&);
  inline dcovector(const _dcovector&);
  inline dcovector(const long&);
  inline dcovector(const char *);
  inline ~dcovector(); //destructor
  
  //// cast ////
  inline operator _zcovector();
  
  //// io ////
  inline double& operator()(const long&);
  inline double operator()(const long&) const;
  inline void set(const long&, const double&) const;
  inline friend std::ostream& operator<<(std::ostream&, const dcovector&);
  inline void write(const char *) const;
  inline void read(const char *);
  
  //// calc ////
  inline friend _drovector t(const dcovector&);
  inline friend double nrm2(const dcovector&);
  inline friend long idamax(const dcovector&);
  inline friend double damax(const dcovector&);
  
  //// misc ////
  inline void clear();
  inline void zero();
  inline void chsign();
  inline void copy(const dcovector&);
  inline void shallow_copy(const _dcovector&);
  inline void resize(const long&);
  inline friend void swap(dcovector&, dcovector&);
  inline friend _dcovector _(dcovector&);
  
  //// unary ////
  inline friend const dcovector& operator+(const dcovector&);
  inline friend _dcovector operator-(const dcovector&);
  
  //// operators with dcovector ////
  inline dcovector& operator=(const dcovector&);
  inline dcovector& operator+=(const dcovector&);
  inline dcovector& operator-=(const dcovector&);
  //// operators with _dcovector ////
  inline dcovector& operator=(const _dcovector&);
  inline dcovector& operator+=(const _dcovector&);
  inline dcovector& operator-=(const _dcovector&);
  //// operators with double ////
  inline dcovector& operator*=(const double&);
  inline dcovector& operator/=(const double&);

  //// + ////
  inline friend _dcovector operator+(const  dcovector&, const  dcovector&);
  inline friend _dcovector operator+(const  dcovector&, const _dcovector&);
  inline friend _dcovector operator+(const _dcovector&, const  dcovector&);
  
  //// - ////
  inline friend _dcovector operator-(const  dcovector&, const  dcovector&);
  inline friend _dcovector operator-(const  dcovector&, const _dcovector&);
  inline friend _dcovector operator-(const _dcovector&, const  dcovector&);
  
  //// * ////
  inline friend _dcovector operator*(const  dgematrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dgematrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dgbmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dgbmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dsymatrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dsymatrix&, const  dcovector&);
  inline friend _dcovector operator*(const  dssmatrix&, const  dcovector&);
  inline friend _dcovector operator*(const _dssmatrix&, const  dcovector&);
  
  inline friend _dgematrix operator*(const  dcovector&, const _drovector&);
  inline friend _dgematrix operator*(const  dcovector&, const  drovector&);
  
  inline friend _dcovector operator*(const     double&, const  dcovector&);
  inline friend _dcovector operator*(const  dcovector&, const     double&);
  
  inline friend     double operator*(const _drovector&, const  dcovector&);
  inline friend     double operator*(const  drovector&, const  dcovector&);
  
  //// / ////
  inline friend _dcovector operator/(const  dcovector&, const     double&);
  
  //// % ////
  inline friend     double operator%(const  dcovector&, const  dcovector&);
  inline friend     double operator%(const  dcovector&, const _dcovector&);
  inline friend     double operator%(const _dcovector&, const  dcovector&);
  
  //// friend class ////
  friend class  dgematrix;
  friend class _dgematrix;
  friend class  dgbmatrix;
  friend class _dgbmatrix;
  friend class  dsymatrix;
  friend class _dsymatrix;
  friend class  dssmatrix;
  friend class _dssmatrix;
  friend class _dcovector;
  friend class  drovector;
  friend class _drovector;  
};
