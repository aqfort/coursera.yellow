#pragma once

#include "date.h"

#include <memory>
#include <iostream>

using namespace std;

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    virtual bool Evaluate(
        const Date& date,
        const string& event
    ) const = 0;
};

class EmptyNode : public Node {
public:
    virtual bool Evaluate(
        const Date& date,
        const string& event
    ) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(
        const Comparison& comp,
        const Date& date
    );

    virtual bool Evaluate(
        const Date& date,
        const string& event
    ) const override;

private:
    const Comparison Comparison_;
    const Date Date_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(
        const LogicalOperation& logical_operation,
        const shared_ptr<Node>& left,
        const shared_ptr<Node>& right
    );

    virtual bool Evaluate(
        const Date& date,
        const string& event
    ) const override;

private:
    const LogicalOperation Logical_Operation_;
    const shared_ptr<Node> Left_, Right_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(
        const Comparison& comp,
        const string& event
    );

    virtual bool Evaluate(
        const Date& date,
        const string& event
    ) const override;

private:
    const Comparison Comparison_;
    const string Event_;
};
