import java.util.*;

public class Solution {
    static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode(int x) {
            val = x;
        }
    }

    enum Dir {LEFT, RIGHT}

    static class EdgeDesc {
        int src;
        Dir dir;
        int dst;

        EdgeDesc(int src, Dir dir, int dst) {
            this.src = src;
            this.dir = dir;
            this.dst = dst;
        }
    }

    static class TreeDesc {
        int root;
        Set<Integer> vertices;
        List<EdgeDesc> edges;

        TreeDesc(int root, Set<Integer> vertices, List<EdgeDesc> edges) {
            this.root = root;
            this.vertices = vertices;
            this.edges = edges;
        }

        static TreeDesc of(int root) {
            return join(root, null, null);
        }

        static TreeDesc join(int root, TreeDesc tdLeft, TreeDesc tdRight) {
            Set<Integer> vertices = new HashSet<>();
            vertices.add(root);
            List<EdgeDesc> edges = new LinkedList<>();

            if (tdLeft != null) {
                vertices.addAll(tdLeft.vertices);
                edges.add(new EdgeDesc(root, Dir.LEFT, tdLeft.root));
                edges.addAll(tdLeft.edges);
            }

            if (tdRight != null) {
                vertices.addAll(tdRight.vertices);
                edges.add(new EdgeDesc(root, Dir.RIGHT, tdRight.root));
                edges.addAll(tdRight.edges);
            }

            return new TreeDesc(root, vertices, edges);
        }
    }

    public ArrayList<TreeNode> generateTrees(int a) {
        return null;
    }

    private static List<TreeDesc> gen(int[] vertices) {
        if (vertices.length == 0) return List.of();
        if (vertices.length == 1) return List.of(TreeDesc.of(vertices[0]));

        List<TreeDesc> result = new LinkedList<>();

        for (int i = 0; i < vertices.length; ++i) {
            int root = vertices[i];
            int[] leftVertices = Arrays.copyOfRange(vertices, 0, i);
            int[] rightVertices = Arrays.copyOfRange(vertices, i + 1, vertices.length);

            List<TreeDesc> leftTrees = gen(leftVertices);
            List<TreeDesc> rightTrees = gen(rightVertices);
        }

        return result;
    }
}
