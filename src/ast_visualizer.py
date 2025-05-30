import os
from graphviz import Digraph
from PIL import Image

def parse_ast(lines):
    root = None
    stack = []

    for line in lines:
        if not line.strip(): continue
        indent = len(line) - len(line.lstrip())
        label = line.strip()

        node_id = str(id(label + str(indent)))
        node = {'id': node_id, 'label': label, 'indent': indent}

        while stack and stack[-1]['indent'] >= indent:
            stack.pop()

        if stack:
            parent = stack[-1]
            parent.setdefault('children', []).append(node)
        else:
            root = node

        stack.append(node)

    return root

def flatten_ast(node):
    flat = set()
    flat.add(node['label'])
    for child in node.get('children', []):
        flat.update(flatten_ast(child))
    return flat

def build_graph(graph, node, parent_id=None, color='lightgray'):
    graph.node(node['id'], node['label'], style='filled', fillcolor=color)
    if parent_id:
        graph.edge(parent_id, node['id'])
    for child in node.get('children', []):
        build_graph(graph, child, node['id'], color)

def highlight_diff_graph(graph, node, parent_id=None, original_set=None):
    label = node['label']
    color = 'lightgreen' if label not in original_set else 'lightgray'
    graph.node(node['id'], label, style='filled', fillcolor=color)
    if parent_id:
        graph.edge(parent_id, node['id'])
    for child in node.get('children', []):
        highlight_diff_graph(graph, child, node['id'], original_set)

def run_visualization(input_path="output.txt", output_folder="."):
    # Ensure output folder exists
    os.makedirs(output_folder, exist_ok=True)

    with open(input_path, "r") as f:
        lines = f.readlines()

    try:
        orig_start = lines.index("Original AST:\n") + 1
        opt_start = lines.index("Optimized AST:\n") + 1
    except ValueError:
        print("❌ Error: 'Original AST:' or 'Optimized AST:' not found in input.")
        return

    orig_ast_lines = [line.rstrip() for line in lines[orig_start:opt_start - 1]]
    opt_ast_lines = [line.rstrip() for line in lines[opt_start:]]

    # Parse ASTs
    orig_ast = parse_ast(orig_ast_lines)
    opt_ast = parse_ast(opt_ast_lines)

    # Compare
    orig_flat = flatten_ast(orig_ast)

    # Build and save original AST
    g1 = Digraph("OriginalAST", format='png')
    build_graph(g1, orig_ast)
    g1.render(filename=os.path.join(output_folder, "original_ast"), cleanup=True)

    # Build and save optimized AST
    g2 = Digraph("OptimizedAST", format='png')
    highlight_diff_graph(g2, opt_ast, original_set=orig_flat)
    g2.render(filename=os.path.join(output_folder, "optimized_ast_highlighted"), cleanup=True)

    # Load and combine both images
    img1 = Image.open(os.path.join(output_folder, "original_ast.png"))
    img2 = Image.open(os.path.join(output_folder, "optimized_ast_highlighted.png"))

    max_height = max(img1.height, img2.height)
    img1 = img1.resize((img1.width, max_height))
    img2 = img2.resize((img2.width, max_height))

    combined_width = img1.width + img2.width
    combined_img = Image.new("RGB", (combined_width, max_height), (255, 255, 255))
    combined_img.paste(img1, (0, 0))
    combined_img.paste(img2, (img1.width, 0))

    final_path = os.path.join(output_folder, "ast_comparison.png")
    combined_img.save(final_path)

    print("✅ AST comparison image saved as:", final_path)


# Optional: allow direct run
if __name__ == "__main__":
    run_visualization("output.txt", ".")
