#include "node.h"



using namespace std;



bool EmptyNode::Evaluate(
	const Date& date,
	const string& event
) const {
	return true;
}

DateComparisonNode::DateComparisonNode(
	const Comparison& comp,
	const Date& date
) :
	Comparison_(comp),
	Date_(date) {}

bool DateComparisonNode::Evaluate(
	const Date& date,
	const string& event
) const {
	if (Comparison_ == Comparison::Equal) {
		return date == Date_;
	} else if (Comparison_ == Comparison::Greater) {
		return date > Date_;
	} else if (Comparison_ == Comparison::GreaterOrEqual) {
		return date >= Date_;
	} else if (Comparison_ == Comparison::Less) {
		return date < Date_;
	} else if (Comparison_ == Comparison::LessOrEqual) {
		return date <= Date_;
	} else {
		return date != Date_;
	}
}

LogicalOperationNode::LogicalOperationNode(
	const LogicalOperation& logical_operation,
	const shared_ptr<Node>& left,
	const shared_ptr<Node>& right
) :
	Logical_Operation_(logical_operation),
	Left_(left),
	Right_(right) {}

bool LogicalOperationNode::Evaluate(
	const Date& date,
	const string& event
) const {
	if (Logical_Operation_ == LogicalOperation::Or) {
		return Left_->Evaluate(date, event) || Right_->Evaluate(date, event);
	} else {
		return Left_->Evaluate(date, event) && Right_->Evaluate(date, event);
	}
}

EventComparisonNode::EventComparisonNode(
	const Comparison& comp,
	const string& event
) :
	Comparison_(comp),
	Event_(event) {}

bool EventComparisonNode::Evaluate(
	const Date& date,
	const string& event
) const {
	if (Comparison_ == Comparison::Equal) {
		return event == Event_;
	} else if (Comparison_ == Comparison::Greater) {
		return event > Event_;
	} else if (Comparison_ == Comparison::GreaterOrEqual) {
		return event >= Event_;
	} else if (Comparison_ == Comparison::Less) {
		return event < Event_;
	} else if (Comparison_ == Comparison::LessOrEqual) {
		return event <= Event_;
	} else {
		return event != Event_;
	}
}
