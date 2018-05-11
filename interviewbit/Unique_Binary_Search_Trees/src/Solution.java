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
}
