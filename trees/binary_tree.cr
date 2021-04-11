class Node
  property value
  property left : Node? = nil
  property right : Node? = nil
  
  def initialize(@value : Int32)
  end
end
  
class BinaryTree
  alias NodeOrNil = (Node | Nil)
  
  property root : Node? = nil
  
  def insert(value) : Node
    @root = insert_recursive(root, value)
  end
  
  def search(value) : Bool
    search_recursive(root, value)
  end
  
  private def search_recursive(node : NodeOrNil, value : Int32) : Bool
    return false if node.nil?
    return true if node.value == value
  
  
    node.value < value ? search_recursive(node.left, value) : search_recursive(node.left, value)
  end
  
  private def insert_recursive(node : NodeOrNil, value : Int32) : Node
    return node = Node.new(value) if node.nil?
  
    if node.value <= value
      node.left = insert_recursive(node.left, value)
    else
      node.right = insert_recursive(node.right, value)
    end
  
    node
  end
end
  
tree = BinaryTree.new

tree.insert(12)
tree.insert(13)
tree.insert(15)
tree.insert(16)
tree.insert(11)

pp tree.search(14)
pp tree.search(15)
  