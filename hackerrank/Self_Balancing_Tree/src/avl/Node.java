package avl;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * https://www.hackerrank.com/challenges/self-balancing-tree/problem
 */
public class Node {
    public int val;
    public int ht;
    public Node left;
    public Node right;

    public Node(int val) {
        this.val = val;
    }

    public Node(int val, int ht, Node left, Node right) {
        this.val = val;
        this.ht = ht;
        this.left = left;
        this.right = right;
    }

    public static Node rotateLeftReturnRoot(Node[] pathFromRoot, Node x) {
        Node y = x.right;

        if (y == null) {
            throw new RuntimeException("Can't left-rotate without the right child");
        }

        Node beta = y.left;
        int htAlpha = x.left == null ? -1 : x.left.ht;
        int htBeta = y.left == null ? -1 : y.left.ht;
        int htGamma = y.right == null ? -1 : y.right.ht;

        y.left = x;
        x.right = beta;

        x.ht = Math.max(htAlpha, htBeta) + 1;
        y.ht = Math.max(x.ht, htGamma) + 1;

        if (pathFromRoot.length <= 0) {
            return y;
        }

        Node parent = pathFromRoot[pathFromRoot.length - 1];

        if (parent.left == x) {
            parent.left = y;
        } else {
            parent.right = y;
        }

        propagateHeight(y, pathFromRoot);

        return pathFromRoot[0];
    }

    public static Node rotateRightReturnRoot(Node[] pathFromRoot, Node y) {
        Node x = y.left;

        if (x == null) {
            throw new RuntimeException("Can't right-rotate without the left child");
        }

        Node beta = x.right;
        int htAlpha = x.left == null ? -1 : x.left.ht;
        int htBeta = x.right == null ? -1 : x.right.ht;
        int htGamma = y.right == null ? -1 : y.right.ht;

        x.right = y;
        y.left = beta;

        y.ht = Math.max(htBeta, htGamma) + 1;
        x.ht = Math.max(htAlpha, y.ht) + 1;

        if (pathFromRoot.length <= 0) {
            return x;
        }

        Node parent = pathFromRoot[pathFromRoot.length - 1];

        if (parent.left == y) {
            parent.left = x;
        } else {
            parent.right = x;
        }

        propagateHeight(x, pathFromRoot);

        return pathFromRoot[0];
    }

    public static void propagateHeight(Node fromChildNode, Node[] ancestorsChain) {
        Node n = fromChildNode;

        for (int i = ancestorsChain.length - 1; i >= 0; --i) {
            Node p = ancestorsChain[i];
            Node sibling = p.left == n ? p.right : p.left;
            int htSibling = sibling == null ? -1 : sibling.ht;

            p.ht = Math.max(n.ht, htSibling) + 1;
            n = p;
        }
    }

    public static Node[] insertReturnPath(Node treeRoot, int val) {
        Node n = new Node(val);
        ArrayList<Node> result = new ArrayList<Node>();
        Node p = treeRoot;

        while (p != null) {
            result.add(p);

            if (p.val > val) {
                if (p.left == null) {
                    p.left = n;
                    break;
                }

                p = p.left;
            } else {
                if (p.right == null) {
                    p.right = n;
                    break;
                }

                p = p.right;
            }
        }

        result.add(n);
        Node[] resultArray = result.toArray(new Node[result.size()]);

        if (resultArray.length > 1) {
            propagateHeight(n, Arrays.copyOfRange(resultArray, 0, resultArray.length - 1));
        }

        return resultArray;
    }

    public static int balanceFactor(Node n) {
        int htLeft = n.left == null ? -1 : n.left.ht;
        int htRight = n.right == null ? -1 : n.right.ht;
        return htLeft - htRight;
    }

    public static Node insertBalancedReturnRoot(Node root, int val) {
        Node[] path = insertReturnPath(root, val);

        if (path.length == 1) {
            return path[0];
        }

        int i = path.length - 1;

        Node gamma = (
            path[i].left != null && path[i].left.val == val ?
            path[i].left :
            path[i].right
        );

        for (; i > 0; --i) {
            Node alpha = path[i - 1];
            Node beta = path[i];

            if (balanceFactor(alpha) == 2 && balanceFactor(beta) == -1) {
                Node[] pathFromRoot = Arrays.copyOfRange(path, 0, i);
                rotateLeftReturnRoot(pathFromRoot, beta);

                Node tmp = gamma;
                gamma = beta;
                beta = tmp;
                path[i] = beta;
            }

            if (
                balanceFactor(alpha) == 2 &&
                (balanceFactor(beta) == 0 || balanceFactor(beta) == 1)
            ) {
                Node[] pathFromRoot = Arrays.copyOfRange(path, 0, i - 1);
                rotateRightReturnRoot(pathFromRoot, alpha);

                Node tmp = alpha;
                alpha = beta;
                beta = tmp;
                path[i - 1] = alpha;
                path[i] = beta;
            }

            if (balanceFactor(alpha) == -2 && balanceFactor(beta) == 1) {
                Node[] pathFromRoot = Arrays.copyOfRange(path, 0, i);
                rotateRightReturnRoot(pathFromRoot, beta);

                Node tmp = gamma;
                gamma = beta;
                beta = tmp;
                path[i] = beta;
            }

            if (
                balanceFactor(alpha) == -2 &&
                (balanceFactor(beta) == 0 || balanceFactor(beta) == -1)
            ) {
                Node[] pathFromRoot = Arrays.copyOfRange(path, 0, i - 1);
                rotateLeftReturnRoot(pathFromRoot, alpha);

                Node tmp = alpha;
                alpha = beta;
                beta = tmp;
                path[i - 1] = alpha;
                path[i] = beta;
            }

            gamma = beta;
        }

        return path[0];
    }
}
