
template <typename T>
class node
{
public:
    T element;
    node<T> *next;
    node<T> *previous;
    node(const T &elem) : element{elem}, next{nullptr}, previous{nullptr} {}
};
