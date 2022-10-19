/* Copyright (C) 2015-2018 Michele Colledanchise -  All Rights Reserved
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

#include "behaviortree_cpp_v3/decorators/state_operator.h"
#include "behaviortree_cpp_v3/bt_factory.h"

namespace BT
{
StateOperator::StateOperator(const std::string& name, NodeStatus check_status) :
  DecoratorNode(name, {} ),
  check_status_(check_status)
{}

NodeStatus StateOperator::tick()
{
  std::string registration_ID = child_node_->registrationName();

  for (const auto node: Tree::transversed_nodes) {
    if (node->registrationName() == registration_ID &&
        (node->status() == check_status_ ||
         node->previousStatus() == check_status_)) {
      return NodeStatus::SUCCESS;
    }
  }

  if (child_node_->type() == NodeType::CONDITION) {
    return NodeStatus::FAILURE;
  }

  // search in past nodes
  NodeStatus result = NodeStatus::FAILURE;
  auto visitor = [this, registration_ID, &result](BT::TreeNode * node) {
    if (node->registrationName() == registration_ID &&
        (node->status() == check_status_ ||
         node->previousStatus() == check_status_)) {
      result = NodeStatus::SUCCESS;
    }
  };

  // front node is always the tree root
  BT::applyRecursiveVisitor(Tree::transversed_nodes.front(), visitor);
  return result;
}

RunningState::RunningState(const std::string& name) :
  StateOperator(name, NodeStatus::RUNNING)
{
  setRegistrationID("IsRunning");
}

SuccessState::SuccessState(const std::string& name) :
  StateOperator(name, NodeStatus::SUCCESS)
{
  setRegistrationID("IsSuccess");
}

FailureState::FailureState(const std::string& name) :
  StateOperator(name, NodeStatus::FAILURE)
{
  setRegistrationID("IsFailure");
}

}
