#ifndef ARRAYSLICE_HPP
#define ARRAYSLICE_HPP
#include <initializer_list>
#include <vector>

// Fully generic version
template <typename T, size_t dim>
class Slice
{
    private:
        T *data;
        const size_t *dims;

    public:
        Slice(T *data_, const size_t *dims_) : data(data_), dims(dims_) { return; }
        Slice(std::vector<T> &v_, const size_t *dims_) : data(&(v_[0])), dims(dims_) { return; }
        Slice(std::vector<T> &v_, const std::initializer_list<size_t> &dims_) : data(&(v_[0])), dims(dims_.begin()) { return; }
        inline Slice<T, dim-1> operator[](const size_t idx)
        {
            const size_t *sdims = &dims[1];
            
            size_t offset = idx;
            for (size_t i = 1; i < dim; i++) {
                offset *= dims[i];
            }

            return Slice<T, dim-1>(data + offset, sdims);
        }

};

// Specialization for "lowest level", similar to a vector.
template<typename T>
class Slice<T, 1>
{
    private:
        T *data;
        const size_t numel;

    public:
        Slice(T *data_, const size_t *numel_) : data(data_), numel(numel_[0]) { return; }
        Slice(std::vector<T> &v_) : data(&(v_[0])), numel(v_.size()) { return; }
        Slice(T *data_, const size_t numel_) : data(data_), numel(numel_) { return; }
        inline T &operator[](const size_t idx) { return data[idx]; }
        inline const T &operator[](const size_t idx) const { return data[idx]; }

};

#endif // ARRAYSLICE_HPP
