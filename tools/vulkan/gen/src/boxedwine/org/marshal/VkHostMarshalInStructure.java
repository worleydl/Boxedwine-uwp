package boxedwine.org.marshal;

import boxedwine.org.VkFunction;
import boxedwine.org.VkParam;

/**
 * Created by James on 8/22/2021.
 */
public class VkHostMarshalInStructure extends VkHostMarshal {
    public void before(VkFunction fn, StringBuilder out, VkParam param) throws Exception {
        if (param.paramType.name.equals("VkAllocationCallbacks")) {
            out.append("    static bool shown; if (!shown && " + param.paramArg + ") { klog(\""+fn.name+":VkAllocationCallbacks not implemented\"); shown = true;}\n");
            out.append("    ");
            out.append(param.paramType.name);
            out.append("* ");
            out.append(param.name);
            out.append(" = NULL;\n");
        } else {
            out.append("    Marshal");
            out.append(param.paramType.name);
            out.append(" local_");
            out.append(param.name);
            out.append("(cpu->memory, ");
            out.append(param.paramArg);
            out.append(");\n");
            out.append("    ");
            out.append(param.paramType.name);
            out.append("* ");
            out.append(param.name);
            out.append(" = &local_");
            out.append(param.name);
            out.append(".s;\n");
            param.paramType.needMarshalIn = true;
        }
    }

    public void after(VkFunction fn, StringBuilder out, VkParam param) throws Exception {

    }
}
