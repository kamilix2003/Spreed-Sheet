
#include <iostream>
#include <utility>
#include "Cell.hpp"

// Constructors
Cell::Cell(const double value) : m_value(value), m_definition(none) {

}

// Getters
double Cell::get_value() const {
    return m_value;
}


// Setters
void Cell::set_map_ptr(const std::shared_ptr<std::map<std::string, Cell>>& map_ptr) {
    m_sheet_map = map_ptr;
}

void Cell::set_definition(Definition definition) {
    m_definition = std::move(definition);
}


void Cell::set_value(const double value) {
    m_value = value;
}


// Evaluation
void Cell::evaluate() {
    switch (m_definition.get_operation()) {
        case none:
            std::cout << "none" << std::endl;
            break;

        case add:
        {
            auto p_consts = m_definition.get_const_vec();
            auto p_args = m_definition.get_args_vec();
            m_value = 0;
            for (auto constant : *p_consts) {
                m_value += constant;
            }

            for (auto& arg : *p_args) {
                std::cout<<arg<<std::endl;
                std::cout<<m_sheet_map->at(arg).get_value()<<std::endl;
            }

            // Why this is not working ???
            // for (auto constant : *(m_definition.get_const_vec())) {
            //     std::cout<<constant<<std::endl;
            // }
        }

            break;

        case mul:
            std::cout<< "Multiplication" << std::endl;
            break;

        default:
            std::cout<<"Wrong operation"<<std::endl;
            break;
    }
}

