// Copyright 2024 Mikhail Sokolskiy
// https://t.me/timeforpeople

/**
 * @file s21_vector.tpp
 *
 * @author Mikhail Sokolskiy (jonellab@student.21-school.ru)
 *
 * @brief Methods of the CPP2_s21_containers project,
 * which implements a library for working with containers.
 *
 * @date 2024-07-27
 *
 * @copyright School-21 (c) 2024
 */

// MAIN_FUNCTIONS/s21_vector.tpp

#ifndef S21_VECTOR_TPP_
#define S21_VECTOR_TPP_


namespace s21 {

/******************************************************
 *                                                    *
 *                   КОНСТРУКТОРЫ                     *
 *                                                    *
 ******************************************************/


// template<typename value_type>
// vector<value_type>::vector() : size_(0), capacity_(0), data_(nullptr) {} // конструктор по умолчанию оказался не нужен

template<typename value_type>
vector<value_type>::vector(size_type n)
                  : size_(n),
                    capacity_(size_),
                    data_(
                        std::make_unique<value_type[]>(capacity_) // вызывается метод для объекта умного указателя, выделяющий память
                        // new value_type[capacity_] // для использования с обычными опасными указателями
                    )
                    {}	//parameterized constructor


template<typename value_type>
vector<value_type>::vector(std::initializer_list<value_type> const &items)
                    : vector(items.begin(), items.begin() + items.size())
                    {}	//initializer list constructor

template <typename value_type>
template <typename NoTypeIn>
vector<value_type>::vector(NoTypeIn first, NoTypeIn last)
                    : vector(last - first) // сначала вызывает параметризированный конструктор в котором создается объект
                    {
                    copy(first, last, data_.get()); //потом копирует данные в область памяти объекта
                    } // универсальный конструктор копирования области данных с first по last


template<typename value_type>
vector<value_type>::vector(const vector &v)
                    : vector(v.data_.get(), v.data_.get() + v.size_)
                    {}	//copy constructor

template<typename value_type>
vector<value_type>::vector(vector &&v) noexcept
                    : size_(exchange(v.size_, 0)),
                    capacity_(exchange(v.capacity_, 0)),
                    data_(exchange(v.data_, nullptr))
                    {}	//move constructor




// template<typename value_type>
// vector<value_type>::~vector() noexcept { if (data_) delete[] data_; } // для случая обычного указателя


/******************************************************
 *                                                    *
 *                    ОПЕРАТОРЫ                       *
 *                                                    *
 ******************************************************/

template<typename value_type>
auto vector<value_type>::operator=(const vector &v) -> vector& {
    if (this != &v) {
        vector Temp(v);  // создаем временную копию
        this->swap(Temp);
    }
    return *this;
}  // copy assignment operator

template<typename value_type>
auto vector<value_type>::operator=(vector &&v) noexcept -> vector& {
    if (this != &v) {
        this->swap(v);
    }
    return *this;
}  // move assignment operator


// квадратные скобки с позицией pos элемента возвращают значение без проверки выхода pos за пределы
template <typename value_type>
auto vector<value_type>::operator[](size_type pos) -> reference {
    return data_[pos]; // неконтролируемый доступ к памяти, возможен выход за пределы и как следствие падение программы
}


/******************************************************
 *                                                    *
 *                      МЕТОДЫ                        *
 *                                                    *
 ******************************************************/


// возвращает текущее значение элемента по позиции pos с проверкой pos на выход за пределы области памяти
template <typename value_type>
auto vector<value_type>::at(size_type pos) -> reference {
    return (pos > size_-1)
           ? (throw std::out_of_range("at(): выход за пределы элементов объекта\n"))
           : data_[pos];
}

// возвращает количество элементов, находящееся сейчас в векторе
template <typename value_type>
auto vector<value_type>::size() -> size_type {
    return size_;
}

// возвращает ёмкость - количество элементов, которые могут быть записаны в вектор без дополнительного выделения памяти
template <typename value_type>
auto vector<value_type>::capacity() -> size_type {
    return capacity_;
}

// возвращает значение нулевого(изначального) элемента вектора
template <typename value_type>
auto vector<value_type>::front() -> const_reference {
    return !empty() ? data_[0] : throw std::out_of_range("front(): объект пустой, невозможно прочитать первый элемент\n");
}

// возвращает значение последнего элемента вектора
template <typename value_type>
auto vector<value_type>::back() -> const_reference {
    return at(size_-1);
}

// возвращает указатель на начало области данных вектора
template <typename value_type>
auto vector<value_type>::data() -> iterator {
    return begin();
}

// возвращает, выделена ли память под вектор
template <typename value_type>
bool vector<value_type>::empty() {
    return size_ == 0;
}

// очищает вектор (на самом деле просто делает невидимыми элементы, но память при этом остаётся)
template <typename value_type>
void vector<value_type>::clear() {
    size_ = 0;
}

// удаляет последний элемент
template <typename value_type>
void vector<value_type>::pop_back() {
    if (!empty()) --size_;
}

// возвращает указатель на первый элемент
template <typename value_type>
auto vector<value_type>::begin() -> iterator {
    return data_.get();
}

// возвращает указатель на последний элемент + 1
template <typename value_type>
auto vector<value_type>::end() -> iterator {
    return begin() + size_;
}

// вставляет новый элемент на позицию pos, при необходимости выделяется удвоенная память
template <typename value_type>
auto vector<value_type>::insert(iterator pos, const_reference value) -> iterator {
    if (pos < begin() || pos > end()) {
        throw std::out_of_range("insert(): выход за границы элементов объекта\n");
    }

    auto position = pos - begin(); // вычисляем позицию вставки от начала выделенной памяти

    if (size_ == capacity_) {
        // выделяем новую память под объект
        size_type new_capacity = (capacity_ == 0  ?
                                                    1
                                                      // если объект пустой, то выделяем 1 ячейку памяти
                                                  : 2 * capacity_
                                                      //если объект под завязку заполнен данными, увеличиваем размер памяти в 2 раза
                                  );
        reserve(new_capacity); // вызов функции выделения памяти
    }

    pos = begin() + position;
    std::move_backward(pos, end(), end() + 1);

        ++size_;

        *pos = value;

    return pos;
}



// удаление элемента в позиции pos со смещением тех что правее от него на -1 позицию влево
template <typename value_type>
void vector<value_type>::erase(iterator pos) {
    if(pos < end() && pos >=begin()) {
        std::move(pos+1, end(), pos);
        pop_back();
      } else std::cerr << "erase(): выход за границы элементов объекта\n";
}

// обмен объектов данными, когда данные первого становятся данными второго и наоборот
template <typename value_type>
void vector<value_type>::swap(vector& other) {

    if (this != &other) {
        std::swap(other.size_, size_);
        std::swap(other.capacity_, capacity_);
        std::swap(other.data_, data_);
    }
}

// подрезание незаполненной памяти до последнего элемента, чтобы size = capacity
// на самом деле выделяется новая область памяти, куда перемещаются элементы
template <typename value_type>
void vector<value_type>::shrink_to_fit() {
        if (   size_ > 0
            &&
               size_ < capacity_
           ) {
                capacity_ = size_ - 1; // временно делаем capacity_ < size_ , иначе reserve не сработает
                reserve(size_);
             } else std::cerr << "shrink_to_fit(): оптимизировать нечего\n";
}

// выделяется новая область памяти большего чем сейчас размера, куда перемещаются элементы
template <typename value_type>
void vector<value_type>::reserve(size_type size) {
    if (size > capacity_) {

        vector Temp(size); // Создаем временный вектор с новой емкостью size
        std::move(begin(), end(), Temp.begin()); // перемещаем данные data_ в Temp.data_

        // Перемещаем временный вектор в текущий с использованием оператора перемещения
        Temp.size_ = size_;
        *this = std::move(Temp);
    }
}


// добавляется новый элемент в конец. При необходимости выделяется новая удвоенная память, куда копируются все элементы
template <typename value_type>
void vector<value_type>::push_back(const_reference value) {
    insert(end(), value);
}

// возвращает максимальное теоретическое количество элементов, которые могут быть записаны в вектор для этого типа данных
template <typename value_type>
auto vector<value_type>::max_size() const noexcept -> size_type {
        return static_cast<size_type>(-1) / sizeof(value_type);
}


                                            template <typename value_type>
                                            template <typename... Args>
vector<typename vector<value_type>::iterator>
                                            vector<value_type>::
            insert_many(iterator pos, Args &&...args) {

                vector<iterator> results(sizeof...(args)); // создаём вектор для вставки адресов на все новые элементы
                                                           // (вектор итераторов, а в нашем случае указателей)

                auto distance = pos - begin(); // запоминаем позицию вставки от начала.
                                               // После реаллокации это нас спасёт, так как итератор pos будет неликвиден

                reserve(size() + sizeof...(args)); // реаллоцируем память на весь список вставки,
                                                   // чтобы не делать это потом и многократно

                pos = begin() + distance; // новый итератор для вставки. Он будет неизменен
                                          // в течение всей вставки, так как мы выделили память на всех новых членов

                //    (results.push_back((pos = insert(pos, std::forward<Args>(args))), ++pos), ...);  // данная реализация всего одной строкой, она будет работать
                                                                                                       // и без предварительной реаллокации, но это вынудит программу
                                                                                                       // делать несколько реаллокаций во время вставки новых элементов
                   (results.push_back(
                                       insert(pos++, std::forward<Args>(args)) // вставляем в вектор начиная с позиции pos друг за дружкой и одновременно смещаем итератор на след. ячейку для вставки
                                      ),  ...);

            return results;  // возвращает вектор с указателями
}                            // на адреса вставленных элементов


                                            template <typename value_type>
                                            template <typename... Args>
void
     vector<value_type>::insert_many_back(Args &&...args) {
        insert_many(end(), args...);
}


} // namespace s21



#endif // S21_VECTOR_TPP_