/* Copyright (C) 2018 Michele Colledanchise -  All Rights Reserved
 * Copyright (C) 2018-2020 Davide Faconti, Eurecat -  All Rights Reserved
*
*   Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
*   to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
*   and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*   The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
*   WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef DECORATOR_STATE_OPERATOR_H
#define DECORATOR_STATE_OPERATOR_H

#include "behaviortree_cpp_v3/decorator_node.h"

namespace BT
{
/**
 * @brief The StateOperator returns SUCCESS if child's previous state
 * was `check_status', or FAILURE otherwise
 */
class StateOperator : public DecoratorNode
{
public:
  StateOperator(const std::string& name, NodeStatus check_status);

  virtual ~StateOperator() override = default;

private:
  BT::NodeStatus check_status_;
  virtual BT::NodeStatus tick() override;
};

/**
 * @brief The RunningState returns SUCCESS if child was RUNNING
 * or FAILURE otherwise
 */
class RunningState : public StateOperator
{
public:
  RunningState(const std::string& name);

  virtual ~RunningState() override = default;
};

/**
 * @brief The SuccessState returns SUCCESS if child was SUCCESS
 * or FAILURE otherwise
 */
class SuccessState : public StateOperator
{
public:
  SuccessState(const std::string& name);

  virtual ~SuccessState() override = default;
};

/**
 * @brief The FailureState returns SUCCESS if child was FAILURE
 * or FAILURE otherwise
 */
class FailureState : public StateOperator
{
public:
  FailureState(const std::string& name);

  virtual ~FailureState() override = default;
};
}

#endif
