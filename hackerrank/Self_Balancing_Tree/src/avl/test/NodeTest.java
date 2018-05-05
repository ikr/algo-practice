package avl.test;

import junit.framework.TestCase;
import avl.Node;

public class NodeTest extends TestCase {
    public void testRootConstructor() {
        Node n = new Node(42);
        assertEquals(42, n.val);
        assertEquals(0, n.ht);
        assertNull(n.left);
        assertNull(n.right);
    }

    public void testGenericConstructor() {
        Node l = new Node(10);
        Node r = new Node(1000);
        Node n = new Node(100, 1, l, r);

        assertEquals(100, n.val);
        assertEquals(1, n.ht);
        assertSame(l, n.left);
        assertSame(r, n.right);
    }

    public void testRotateLeftOnRoot() {
        Node alpha = new Node(1);
        Node beta = new Node(3);
        Node gamma = new Node(5);

        Node y = new Node(4, 1, beta, gamma);
        Node x = new Node(2, 2, alpha, y);

        Node newRoot = Node.rotateLeftReturnRoot(new Node[0], x);

        assertSame(y, newRoot);
        assertEquals(2, y.ht);
        assertSame(x, y.left);
        assertSame(gamma, y.right);

        assertSame(alpha, x.left);
        assertSame(beta, x.right);
        assertEquals(1, x.ht);
    }

    public void testRotateLeftOnNonRoot1() {
        Node y = new Node(0);
        Node x = new Node(0, 1, null, y);
        Node delta = new Node(0, 2, x, null);
        Node root = new Node(0, 3, null, delta);
        Node[] path = {root, delta};

        Node newRoot = Node.rotateLeftReturnRoot(path, x);
        assertSame(root, newRoot);
        assertSame(delta.left, y);
    }

    public void testRotateLeftOnNonRoot2() {
        Node y = new Node(0);
        Node x = new Node(0, 1, null, y);
        Node delta = new Node(0, 2, null, x);
        Node root = new Node(0, 3, delta, null);
        Node[] path = {root, delta};

        Node newRoot = Node.rotateLeftReturnRoot(path, x);
        assertSame(root, newRoot);
        assertSame(delta.right, y);
    }

    public void testRotateLeftThrowsRuntimeExceptionWhenNoRightChild() {
        try {
            Node.rotateLeftReturnRoot(new Node[0], new Node(42));
            fail("Must have thrown");
        } catch (RuntimeException ex) {
            assertEquals("Can't left-rotate without the right child", ex.getMessage());
        }
    }

    public void testRotateRightReversesTheLeftRotation() {
        Node alpha = new Node(1);
        Node beta = new Node(3);
        Node gamma = new Node(5);

        Node y = new Node(4, 1, beta, gamma);
        Node x = new Node(2, 2, alpha, y);

        Node.rotateLeftReturnRoot(new Node[0], x);
        Node newRoot = Node.rotateRightReturnRoot(new Node[0], y);

        assertSame(x, newRoot);
        assertSame(alpha, x.left);
        assertSame(y, x.right);
        assertEquals(2, x.ht);

        assertSame(beta, y.left);
        assertSame(gamma, y.right);
        assertEquals(1, y.ht);
    }

    public void testPorpagateHeightInDegenerateCase() {
        Node n = new Node(13);
        Node.propagateHeight(n, new Node[0]);
        assertEquals(0, n.ht);
    }

    public void testPropagateHeightInZigzagCase() {
        Node d = new Node(9);
        Node c = new Node(10, 1, d, null);
        Node b = new Node(8, 2, null, c);
        Node a = new Node(16, 3, b, null);

        d.ht = 100;
        Node[] path = {a, b, c};
        Node.propagateHeight(d, path);

        assertEquals(101, c.ht);
        assertEquals(102, b.ht);
        assertEquals(103, a.ht);
    }

    public void testInsertReturnPathOnEmptyTree() {
        Node[] path = Node.insertReturnPath(null, 1929);

        assertEquals(1, path.length);
        assertEquals(1929, path[0].val);
    }

    public void testInsertReturnPathDeepOnTheLeft() {
        Node d = new Node(11);
        Node c = new Node(10, 1, null, d);
        Node b = new Node(8, 2, null, c);
        Node a = new Node(16, 3, b, null);

        Node[] path = Node.insertReturnPath(a, 7);

        assertEquals(3, path.length);
        assertSame(a, path[0]);
        assertSame(b, path[1]);

        Node n = path[2];
        assertEquals(7, n.val);
        assertSame(n, b.left);

        assertEquals(2, b.ht);
        assertEquals(3, a.ht);
    }

    public void testInsertReturnPathDeepOnTheRight() {
        Node d = new Node(11);
        Node c = new Node(10, 1, null, d);
        Node b = new Node(8, 2, null, c);
        Node a = new Node(16, 3, b, null);

        Node[] path = Node.insertReturnPath(a, 12);

        assertEquals(5, path.length);
        assertSame(a, path[0]);
        assertSame(b, path[1]);
        assertSame(c, path[2]);
        assertSame(d, path[3]);

        Node n = path[4];
        assertEquals(12, n.val);
        assertSame(n, d.right);

        assertEquals(1, d.ht);
        assertEquals(2, c.ht);
        assertEquals(3, b.ht);
        assertEquals(4, a.ht);
    }

    public void testBalanceFactorOnNodeWithoutChildren() {
        assertEquals(0, Node.balanceFactor(new Node(25)));
    }

    public void testBalanceFactorOnNodeWithTwoChildren() {
        assertEquals(
            -1,
            Node.balanceFactor(
                new Node(
                    0,
                    0,
                    new Node(0, 1, null, null),
                    new Node(0, 2, null, null)
                )
            )
        );
    }

    public void testBalanceFactorOnProblemStatementExample() {
        Node[] path = Node.insertReturnPath(tree2345(), 6);

        assertEquals(0, Node.balanceFactor(path[3]));
        assertEquals(-1, Node.balanceFactor(path[2]));
        assertEquals(-2, Node.balanceFactor(path[1]));
        assertEquals(-2, Node.balanceFactor(path[0]));
    }

    public void testInsertBalancedReturnRootOnEmptyTree() {
        Node root = Node.insertBalancedReturnRoot(null, 52);
        assertEquals(52, root.val);
        assertEquals(0, root.ht);
        assertNull(root.left);
        assertNull(root.right);
    }

    public void testInsertBalancedReturnRootWorksOnOneNodeTree() {
        Node root = Node.insertBalancedReturnRoot(new Node(10), 9);
        assertEquals(root.left.val, 9);
    }

    public void testInsertBalancedReturnRootOnProblemStatementExample() {
        Node root = Node.insertBalancedReturnRoot(tree2345(), 6);
        Node n5 = root.right;

        assertEquals(5, n5.val);
        assertEquals(4, n5.left.val);
        assertEquals(6, n5.right.val);
        assertEquals(2, root.left.val);
        assertEquals(3, root.val);
    }

    private static Node tree2345() {
        Node n5 = new Node(5);
        Node n4 = new Node(4, 1, null, n5);
        Node n2 = new Node(2);
        Node n3 = new Node(3, 2, n2, n4);

        return n3;
    }
}
